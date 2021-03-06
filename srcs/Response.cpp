/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:42:45 by ellarbi           #+#    #+#             */
/*   Updated: 2022/01/31 21:21:21 by ellarbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/Response.hpp"

# define BUF_SIZE 500

Response::Response(execRequest &my_data, int socket, Server &serv) :  
	_data(my_data), _socket(socket), _buf(NULL), _idx(0), _buf_size(0)
{
	if (this->_data.getBuf())
	{
		this->_buf = NULL;
		this->_buf_size = this->_data.getBufSize();
		this->_buf = new unsigned char[this->_buf_size + 1];
		std::memmove(this->_buf, this->_data.getBuf(), this->_buf_size);
		this->_data.free_buf();
	}
	this->_headers["Status"] = this->_data.getEnvVar("STATUS_CODE");
	if (!this->_data.getEnvVar("LOCATION").empty())
		this->_headers["Location"] = this->_data.getEnvVar("LOCATION");
	if (this->_data.getCgi())
		this->parse_data_buf();
	this->_headers["Content-Length"] = ft_itoa_cpp(this->_buf_size);
	this->setDate();
	this->setLastModified();
	this->_headers["Server"] = std::string("webserv/4.2");
	this->check_content_type();
	this->send_response(serv);

}

Response::~Response()
{
	this->_headers.clear();
}

void		Response::parse_data_buf()
{
	if (!this->_buf)
		return ;

	while (std::memchr(this->_buf + this->_idx, ':', this->_buf_size - 1)) // check if there is still header-fields
	{
		if ((&this->_buf[this->_idx])[0] == '\r') // end of the header 
			break ;
		int next_n = 0;
		while (1)
		{
			if (std::memchr(this->_buf + this->_idx + next_n, '\n', 1))
				break ;
			next_n++;
		}
		std::string tmp_s = std::string((char *)(&this->_buf[this->_idx]), next_n - 1); //line with the header field
		
		// "erase" the line from buf
		this->_idx += next_n + 1;
		this->_buf_size -= next_n + 1;

		std::string name = tmp_s.substr(0, tmp_s.find(':')); // separate the field-name
		if (name[0] != 'X')
		{
			if (name.compare("Content-type") == 0)
				name = "Content-Type";
			this->_headers[name] = tmp_s.substr(tmp_s.find(':') + 2, tmp_s.size()); // put the name and value in the _header map
		}
	}
	if ((&this->_buf[this->_idx])[0] == '\r' && (&this->_buf[this->_idx])[1] == '\n')
	{
		this->_idx += 2;
		this->_buf_size -= 2;
	}
}


void		Response::setDate()
{
	time_t			date;
	
	time(&date);
	this->_headers["Date"] = this->formatDate(date);
}

void			Response::setLastModified()
{
	if (this->_data.getLastModified() > 0)
		this->_headers["Last-Modified"] = this->formatDate(this->_data.getLastModified());
}

std::string		Response::formatDate(time_t timestamp)
{
	//GMT time is 2 hour behind localtime in france (summer hour otherwhise it's 1 hour behind)
	char			buffer[30];
 
	struct tm tm = *gmtime(&timestamp);
	strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", &tm);
	return std::string(buffer);
}

void			Response::writeStatusLine()
{
	// Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
	if (this->_headers.find("Status") != this->_headers.end())
	{
		this->_response = this->_data.getEnvVar("SERVER_PROTOCOL") + ' '; // HTTP-Version SP 
		this->_response += this->_headers.find("Status")->second + "\r\n"; // Status-Code SP Reason-Phrase CRLF
		this->_headers.erase("Status"); // Erase status from header to not print it as a header field
	}
}

void			Response::format_header()
{
	// header-field = field-name ":" OWS field-value OWS CRLF
	std::map<std::string, std::string>::iterator it = this->_headers.begin();
	for (; it != this->_headers.end(); it++)
	{
		if (!(it->second.empty()))
		{
			std::string tmp = it->first + ": " + this->_headers.find(it->first)->second + "\r\n";
			this->_response.append(tmp);
		}
	}
}

void		Response::check_content_type()
{
	std::string tmp(this->_data.getEnvVar("PATH_INFO"));
	if (tmp.find('.') != std::string::npos)
	{
		tmp.erase(0, tmp.find_last_of('.') + 1);
		if (!tmp.compare("css"))
			this->_headers["Content-Type"] = "text/css";
		else if (!tmp.compare("jpeg") || !tmp.compare("jpg") || !tmp.compare("png"))
			this->_headers["Content-Type"] = "image/" + tmp;
		else if (!tmp.compare("html"))
			this->_headers["Content-Type"] = "text/html";
	}
}


void			Response::send_response(Server &serv)
{
	char *to_send = NULL;
	int size;
	this->_response.clear();
	this->_response_c = NULL;
	// status line
	this->writeStatusLine();
	// Headers
	this->format_header();
	//CRLF to separate header and body (or end)
	this->_response.append("\r\n"); 
	// Message-Body
	size = this->_response.size() + this->_buf_size;
	to_send = new char[size];
	std::memmove(to_send, this->_response.c_str(), this->_response.size());
	if (this->_buf)
	{
		std::memmove(to_send + this->_response.size(), this->_buf + this->_idx, this->_buf_size);
		delete [] this->_buf;
	}
	//print on our cout to check
	std::cout << "------------ RESPONSE -----------------" << std::endl;
	write(1, to_send, size);
	std::cout << "---------------------------------------" << std::endl;
	// Actually sending to socket
	int send_ret  = send(this->_socket, to_send, size, 0);
	if (send_ret < 0)
	{
		delete [] to_send;
		to_send = NULL;
		close(serv.getClientSocket());
	}

	else if (send_ret >= 0)
	{
		delete [] to_send;
		to_send = NULL;
	}
}
