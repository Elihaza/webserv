/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellarbi <ellarbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 14:13:12 by ellarbi           #+#    #+#             */
/*   Updated: 2022/01/31 21:22:27 by ellarbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/parsing.hpp"

// **************************************** //
// ***********  PARSING SERVER  *********** //
// **************************************** //

/*************************************************************************/


/* Code fait par Rayane*/

void count_word_one_err(const std::string &str, const std::string &cle)
{
    (void)cle;
    size_t i = 0;
   bool inSpaces = true;
   int numWords = 0;

   while (str[i])
   {
        if (str[i] == ';')
            break;
      if (std::isspace(str[i]) || str[i] == '{' || str[i] == ';')
      {
         inSpaces = true;
      }
      else if (inSpaces)
      {
         numWords++;
         inSpaces = false;
      }

      i++;
   }

   if (numWords == 1)
   {
       std::cout << "Error : probleme dans la ligne avec le mot cle " << cle << std::endl;
       exit(EXIT_FAILURE);
   }
}


void    check_fichier_valide_index(const std::string &str, size_t addr_index)
{
    int a = 0;
    count_word_one_err(str, "index");
    while (str[addr_index])
    {
        while (std::isspace(str[addr_index]))
            addr_index++;
        if (str[addr_index] == ';')
            break;
        while (!std::isspace(str[addr_index]) && str[addr_index] != ';')
        {
            if (str[addr_index] ==  '.')
                a++;
            addr_index++;
        }

        if (a != 1)
        {
            std::cout << "Error : probleme dans la ligne du mot cle index" << std::endl;
            exit(EXIT_FAILURE);
        }
        a = 0;
        addr_index++;
    }

}

int count_word_two_and_four(const std::string &str, std::string &cle)
{
    (void)cle;
    size_t i = 0;
   bool inSpaces = true;
   int numWords = 0;

   while (str[i])
   {
        if (str[i] == ';')
            break;
      if (std::isspace(str[i]) || str[i] == '{' || str[i] == ';')
      {
         inSpaces = true;
      }
      else if (inSpaces)
      {
         numWords++;
         inSpaces = false;
      }

      i++;
   }

    std::cout << "nombre de mot = " << numWords << std::endl;
   if (numWords > 4 || numWords == 1)
   {
       std::cout << "Error : probleme dans la ligne avec le mot cle " << cle << std::endl;
       exit(EXIT_FAILURE);
   }
   return numWords;

}

void count_word_three(const std::string &str, std::string &cle)
{
    (void)cle;
    size_t i = 0;
   bool inSpaces = true;
   int numWords = 0;

   while (str[i])
   {
        if (str[i] == ';')
            break;
      if (std::isspace(str[i]) || str[i] == '{' || str[i] == ';')
      {
         inSpaces = true;
      }
      else if (inSpaces)
      {
         numWords++;
         inSpaces = false;
      }

      i++;
   }

    std::cout << "nombre de mot = " << numWords << std::endl;
   if (numWords > 3 || numWords == 1)
   {
       std::cout << "Error : probleme dans la ligne avec le mot cle " << cle << std::endl;
       exit(EXIT_FAILURE);
   }

}

void count_word_two(const std::string &str, std::string &cle)
{
    (void)cle;
    size_t i = 0;
   bool inSpaces = true;
   int numWords = 0;

   while (str[i])
   {
        if (str[i] == ';')
            break;
      if (std::isspace(str[i]) || str[i] == '{' || str[i] == ';')
      {
         inSpaces = true;
      }
      else if (inSpaces)
      {
         numWords++;
         inSpaces = false;
      }

      i++;
   }

    std::cout << "nombre de mot = " << numWords << std::endl;
   if (numWords > 2 || numWords == 1)
   {
       std::cout << "Error : probleme dans la ligne avec le mot cle " << cle << std::endl;
       exit(EXIT_FAILURE);
   }

}

void check_arg_key_after(const std::string &str, size_t delimiteur, const std::string cle, const std::string arg)
{
    size_t k = delimiteur + arg.size() + 1;


    std::cout << "str [k] = " << str[k ] << std::endl;

    if (str[k - 1] != ' '  && str[k - 1] != '\n' && str[k - 1] != '\t' && str[k - 1] != '\n' 
      && str[k - 1] != '\r' && str[k - 1] != '\v' && str[k - 1] != '\f' && str[k - 1] != ';')
    {
        std::cout << "Error : mauvais argument apres le mot cle " << cle <<  std::endl;
        exit(EXIT_FAILURE); 
    }
}

void check_arg_key_before(const std::string &str, size_t delimiteur, const std::string cle)
{

    if (str[delimiteur - 1] != ' ' && str[delimiteur - 1] != '\n' && str[delimiteur - 1] != '\t' && str[delimiteur - 1] != '\n'
        && str[delimiteur - 1] != '\r' && str[delimiteur - 1] != '\v' && str[delimiteur - 1] != '\f')
    {
        std::cout << "Error : mauvais argument apres le mot cle " << cle <<  std::endl;
        exit(EXIT_FAILURE);
    }
    
}

void check_nothing(const std::string &str)
{
    size_t k = 0;

    while (str[k])
    {
         if (str[k] != ' '  && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
         && str[k] != '\r' && str[k] != '\v' && str[k] != '\f' && str[k] != '{' && str[k] != '}')
         {
            std::cout << "Error : mot cle inconnu = " << str <<   std::endl;
            exit(EXIT_FAILURE);
         }
         k++;
    }
}

void check_before_key(const std::string &str, size_t delimiteur, std::string cle)
{
    size_t k = 0;
    while(str[k] == ' '  || str[k] == '\n' || str[k] == '\t' || str[k] == '\n' 
    || str[k] == '\r' || str[k] == '\v' || str[k] == '\f')
        k++;
    if (k != delimiteur)
    {
        std::cout << "Erreur : character interdit avant le mot cle " << cle <<  std::endl;
        exit(EXIT_FAILURE);
    }
}

void check_max_body_size(const std::string &str, size_t addr_index)
{
   addr_index = str.find("max_body_size");
    std::string cle = "max_body_size";
    check_before_key(str, addr_index, cle);
    size_t  k = addr_index + 13;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle methode_body_size" << std::endl;
        exit(EXIT_FAILURE);
    }
    count_word_two(str, cle);

    while (str[k] == ' ' || str[k] == '\n' || str[k] == '\t' || str[k] == '\n' 
            || str[k] == '\r' || str[k] == '\v' || str[k] == '\f')
    {
        k++;
    }

    while(isdigit(str[k]))
        k++;

    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f' && str[k] != ';')
    {
        std::cout << "Error : probleme dans la ligne du mot cle methode_body_size" << std::endl;
        exit(EXIT_FAILURE);
    }
   


}

void check_return(const std::string &str, size_t addr_index)
{
    //size_t k = 0;
    addr_index = str.find("return");
    std::string cle = "return";
    check_before_key(str, addr_index, cle);
    size_t  k = addr_index + 6;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle return" << std::endl;
        exit(EXIT_FAILURE);
    }
    count_word_three(str, cle);

    size_t indicateur = 0;
    while (std::isspace(str[k]))
    {
        k++;
    }

    while(isdigit(str[k]) && !std::isspace(str[k]))
        k++;

    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f' && str[k] != ';')
    {
        std::cout << "Error : probleme dans la ligne du mot cle return" << std::endl;
        exit(EXIT_FAILURE);
    }
   

    if(str.find("http://localhost:8080/redirect_here/redirect.html") != std::string::npos)
    {
        check_arg_key_before(str, str.find("http://localhost:8080/redirect_here/redirect.html"), cle);
        check_arg_key_after(str, str.find("http://localhost:8080/redirect_here/redirect.html"), cle, "http://localhost:8080/redirect_here/redirect.html");

    }
    else if (str.find("http://localhost:8080/img/42.png") != std::string::npos)
    {
        check_arg_key_before(str, str.find("http://localhost:8080/img/42.png"), cle);
        check_arg_key_after(str, str.find("http://localhost:8080/img/42.png"), cle, "http://localhost:8080/img/42.png");
    }
    else
    {
        std::cout << "Error : mauvais argument mot return" << std::endl;
        exit(EXIT_FAILURE);
    }

}

void  check_index(const std::string &str, size_t addr_index)
{
    addr_index = str.find("index");
    std::string cle = "index";
    check_before_key(str, addr_index, cle);
    size_t  k = addr_index + 5;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle index" << std::endl;
        exit(EXIT_FAILURE);
    }

    k = addr_index + 5;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle index" << std::endl;
        exit(EXIT_FAILURE);
    }

    check_fichier_valide_index(str, k);
}

void  check_upload_path(const std::string &str, size_t addr_index)
{
    //size_t k = 0;
    addr_index = str.find("upload_path");
    std::string cle = "upload_path";
    check_before_key(str, addr_index, cle);
    size_t  k = addr_index + 11;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle upload_path" << std::endl;
        exit(EXIT_FAILURE);
    }
    count_word_two(str, cle);
    
    int a = 0;
    addr_index = k;
    while (str[addr_index])
    {
        while (std::isspace(str[addr_index]))
        {
            std::cout << "str[addr_index] = " << str[addr_index] << std::endl; 
            addr_index++;
        }
        if (str[addr_index] == ';')
            break;
        while (!std::isspace(str[addr_index]) && str[addr_index] != ';')
        {
            std::cout << "str[addr_index] = " << str[addr_index] << std::endl; 
            if (str[addr_index] ==  '/')
                a++;
            addr_index++;
        }

        if (a != 1)
        {
            std::cout << "Error : probleme dans la ligne du mot cle upload" << std::endl;
            exit(EXIT_FAILURE);
        }
        addr_index++;
    }

    // if(str.find("/download") != std::string::npos)
    // {
    //     check_arg_key_before(str, str.find("/download"), cle);
    //     check_arg_key_after(str, str.find("/download"), cle, "/download");

    // }

    // else
    // {
    //     std::cout << "Error : mauvais argument mot cle upload" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
}

void  check_cgi_path(const std::string &str, size_t addr_index)
{
    addr_index = str.find("cgi_path");
    std::string cle = "cgi_path";
    check_before_key(str, addr_index, cle);
    size_t  k = addr_index + 8;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle cgi_path" << std::endl;
        exit(EXIT_FAILURE);
    }
    k = addr_index + 8;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle cgi_path" << std::endl;
        exit(EXIT_FAILURE);
    }
    count_word_two(str, cle);

    if(str.find("/usr/bin/php-cgi") != std::string::npos)
    {
        check_arg_key_before(str, str.find("/usr/bin/php-cgi"), cle);
        check_arg_key_after(str, str.find("/usr/bin/php-cgi"), cle, "/usr/bin/php-cgi");
    }
    else
    {
        std::cout << "Error : mauvais argument mot cle cgi_path" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void  check_accepted_method(const std::string &str, size_t addr_index)
{
    addr_index = str.find("accepted_method");
    std::string cle = "accepted_method";
    check_before_key(str, addr_index, cle);
    size_t  k = addr_index + 15;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle accepted_method" << std::endl;
        exit(EXIT_FAILURE);
    }

    size_t indicateur = count_word_two_and_four(str, cle);

    if (indicateur == 4)
    {
        if(str.find("GET") != std::string::npos && str.find("POST") != std::string::npos && str.find("DELETE") != std::string::npos)
        {


            if (str.find("GET") != std::string::npos)
            {
                check_arg_key_before(str, str.find("GET"), cle);
                check_arg_key_after(str, str.find("GET"), cle, "GET");
            }
            else
            {

                std::cout << "Error : mauvais argument mot cle accepted_method" << std::endl;
                exit(EXIT_FAILURE);
            }
            
            if (str.find("DELETE") != std::string::npos)
            {
                
                check_arg_key_before(str, str.find("DELETE"), cle);
                check_arg_key_after(str, str.find("DELETE"), cle, "DELETE");
            }
            else
            {

                std::cout << "Error : mauvais argument mot cle accepted_method" << std::endl;
                exit(EXIT_FAILURE);
            }

            if (str.find("POST") != std::string::npos)
            {
                check_arg_key_before(str, str.find("POST"), cle);
                check_arg_key_after(str, str.find("POST"), cle, "POST");
            }
            else
            {

                std::cout << "Error : mauvais argument mot cle accepted_method" << std::endl;
                exit(EXIT_FAILURE);
            }

        }

        else
        {
                std::cout << "Error : mauvais argument mot cle accepted_method" << std::endl;
                exit(EXIT_FAILURE);
        }
    }

    if (indicateur == 2)
    {
        if (str.find("GET") != std::string::npos)
        {
                check_arg_key_before(str, str.find("GET"), cle);
                check_arg_key_after(str, str.find("GET"), cle, "GET");
        }
        else if (str.find("DELETE") != std::string::npos)
        {
                check_arg_key_before(str, str.find("DELETE"), cle);
                check_arg_key_after(str, str.find("DELETE"), cle, "DELETE");
        }
        else if (str.find("POST") != std::string::npos)
        {
                check_arg_key_before(str, str.find("POST"), cle);
                check_arg_key_after(str, str.find("POST"), cle, "POST");
        }
        else
        {
            std::cout << "Error : mauvais argument mot cle accepted_method" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    if (indicateur == 3)
    {
        size_t a = 0;
        if (str.find("GET") != std::string::npos)
           a++;
        if (str.find("POST") != std::string::npos)
           a++;
        if (str.find("DELETE") != std::string::npos)
           a++;
        if (a != 2)
        {
            std::cout << "Error : mauvais argument mot cle accepted_method" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
}

void  check_location(const std::string &str, size_t addr_index)
{
    addr_index = str.find("location");
    std::string cle = "location";
    check_before_key(str, addr_index, cle);
    size_t  k = addr_index + 8;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle location" << std::endl;
        exit(EXIT_FAILURE);
    }

    count_word_two(str, cle);

    while (std::isspace(str[k]))
        k++;
    
    if (str[k] != '/')
    {
        std::cout << "Error : porbleme dans la ligne avec le mot cle location" << std::endl;
        exit(0);
    }
    if (str[++k] == '/')
    {
        std::cout << "Error : porbleme dans la ligne avec le mot cle location" << std::endl;
        exit(0);
    }

    while(!std::isspace(str[k]))
    {
        if (str[k] == '/' && str[k + 1] == '/')
        {
            std::cout << "Error : porbleme dans la ligne avec le mot cle location" << std::endl;
             exit(0);
        }
        k++;
    }





    std::cout << "str = " << str << std::endl;
    //check_after_key(str, addr_index, cle);

    // if (str.find("/download") != std::string::npos)
    // {
    //     addr_index = str.find("/download");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/download");
    //     count_word_two(str, cle);
    // }

    // else if (str.find("/bonjour_yeah") != std::string::npos)
    // {
    //     addr_index = str.find("/bonjour_yeah");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/bonjour_yeah");
    //     count_word_two(str, cle);
    // }
    // else if (str.find("/Yeah") != std::string::npos)
    // {
    //     addr_index = str.find("/Yeah");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/Yeah");
    //     count_word_two(str, cle);
    // }
    // else if (str.find("/redirect") != std::string::npos)
    // {
    //     addr_index = str.find("/redirect");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/redirect");
    //     count_word_two(str, cle);
    // }
    // else if (str.find("/bonjour_yeah") != std::string::npos)
    // {
    //     addr_index = str.find("/bonjour_yeah");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/bonjour_yeah");
    //     count_word_two(str, cle);
    // }
    // else if (str.find("/code_is_fun") != std::string::npos)
    // {
    //     addr_index = str.find("/code_is_fun");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/code_is_fun");
    //     count_word_two(str, cle);
    // }
    // else if (str.find("/directory") != std::string::npos)
    // {
    //     addr_index = str.find("/directory");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/directory");
    //     count_word_two(str, cle);
    // }
    // else if (str.find("/img") != std::string::npos)
    // {
    //     addr_index = str.find("/img");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/img");
    //     count_word_two(str, cle);
    // }
    
    // else if (str.find("/post_body") != std::string::npos)
    // {
    //     addr_index = str.find("/post_body");
    //     check_arg_key_before(str, addr_index, cle);
    //     check_arg_key_after(str, addr_index, cle, "/post_body");
    //     count_word_two(str, cle);
    // }
    
    //  else
    //  {
    //      size_t j = 0;
    //      size_t i = 0;
    //      while (str[j])
    //      {
    //          if (str[j] == '/')
    //             i++;
    //         j++;
    //      }
    //     if (i > 1)
    //     {
    //         std::cout << "Error : mot cle location" << std::endl;
    //         exit(EXIT_FAILURE);
    //     }
    //     else
    //     {
    //         addr_index = str.find("/");
    //         check_arg_key_before(str, addr_index, cle);
    //         check_arg_key_after(str, addr_index, cle, "/");
    //         count_word_two(str, cle);
    //     }

    //  }
   // exit(0);
}

void  check_error_page(const std::string &str, size_t addr_index)
{
    size_t k = 0;
    std::string cle = "error_page";
    addr_index = str.find("error_page");
    check_before_key(str, addr_index, cle);
    k = addr_index + 10;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle error_page" << std::endl;
        exit(EXIT_FAILURE);
    }

    /* mettre quelque securite*/
}

void  check_autoindex(const std::string &str, size_t addr_index)
{
    /*regarder si avant le mot cle j'ai un character interdit*/
    size_t k = 0;
    std::string cle = "autoindex";
    addr_index = str.find("autoindex");
    check_before_key(str, addr_index, cle);
    /*regarder si apres le mot cle j'ai un character interdit*/
    k = addr_index + 9;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
        && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle autoindex" << std::endl;
        exit(EXIT_FAILURE);
    }
    size_t addr_off = str.find("off");
    size_t addr_on = str.find("on");

    if (addr_on == std::string::npos && addr_off == std::string::npos)
    {
        std::cout << "Error: autoindex ni sur on ni sur off" << std::endl;
        exit(EXIT_FAILURE);
    }

    
    count_word_two(str, cle);
    
    if (addr_on != std::string::npos)
    {
        check_arg_key_before(str, addr_on, cle);
        check_arg_key_after(str, addr_on, cle, "on");
    }
    
    if (addr_off != std::string::npos)
    {
        check_arg_key_before(str, addr_off, cle);
        check_arg_key_after(str, addr_off, cle, "off");
    }
    
}

void  check_root(const std::string &str, size_t addr_index)
{
    size_t k = 0;
    std::string cle = "root";
    addr_index = str.find("root");
    while(str[k] == ' '  || str[k] == '\n' || str[k] == '\t' || str[k] == '\n' 
    || str[k] == '\r' || str[k] == '\v' || str[k] == '\f')
    {
        k++;
    }
    
    if (k != addr_index)
    {
        addr_index = str.find("location");
        if (addr_index == std::string::npos)
        {
            /*probleme a cause du location/root_yeah*/
            std::cout << "Erreur : character interdit avant le mot cle root" << std::endl; 
            exit(EXIT_FAILURE);
        }
    }
    k = addr_index + 4;
    if (str[k] != ' ' && str[k] != '\n' && str[k] != '\t' && str[k] != '\n' 
            && str[k] != '\r' && str[k] != '\v' && str[k] != '\f')
    {
        std::cout << "Error : character interdit apres le mot cle root" << std::endl;
        exit(EXIT_FAILURE);
    }
    count_word_two(str, cle);

    while (str[k])
    {
        if (str[k] == '/' && str[k + 1] == '/')
        {
            std::cout << "Error : mauvais argument mot cle root" << std::endl;
            exit(EXIT_FAILURE);
        }


        k++;
    }

    // if (str.find("/YoupiBanane/bonjour_yeah") != std::string::npos)
    // {
    //     check_arg_key_before(str, str.find("/YoupiBanane/bonjour_yeah"), cle);
    //     check_arg_key_after(str, str.find("/YoupiBanane/bonjour_yeah"), cle, "/YoupiBanane/bonjour_yeah");
    // }
    // else if(str.find("/YoupiBanane") != std::string::npos)
    // {
    //     check_arg_key_before(str, str.find("/YoupiBanane"), cle);
    //     check_arg_key_after(str, str.find("/YoupiBanane"), cle, "/YoupiBanane");

    // }
    // else
    // {
    //     std::cout << "Error : mauvais argument mot cle root" << std::endl;
    //     exit(EXIT_FAILURE);
    // }
    
}

void  check_server_name(const std::string &str, size_t addr_index)
{
    /*regarder si avant le mot cle j'ai un character interdit*/
    size_t k = 0;
    std::string cle = "server_name";
    addr_index = str.find("server_name");
    check_before_key(str, addr_index, cle);
    if (str[addr_index + 11] != ' ')
    {
        std::cout << "Error : character interdit apres le mot cle server_name" << std::endl;
        exit(EXIT_FAILURE);
    }
    /*regarder si apres le mot cle j'ai un character interdit*/
   count_word_two(str, cle);
}

void  check_listen(const std::string &str, size_t addr_index)
{
    std::string cle = "listen";
    addr_index = str.find("listen");
    check_before_key(str, addr_index, cle);
    if (str[addr_index + 6] != ' ')
    {
        std::cout << "Error : character interdit apres le mot cle listen" << std::endl;
        exit(EXIT_FAILURE);
    }
}

void check_line_parsing(std::vector<std::string> &vect)
{
    /*fonction qui check tous les mot cle en appelant leur fonction et renvoi une erreur si il y a des ligne ou on met n'importe quoi*/
    size_t  addr_index = 0;
    std::vector<std::string>::iterator it = vect.begin();
    for (; it != vect.end() ; it++)
    {
        if (it->find("listen") != std::string::npos)
        {
            check_listen(*it, addr_index);
        }
        
        else if (it->find("server_name") != std::string::npos)
        {
            check_server_name(*it, addr_index);
        }
        else if (it->find("root") != std::string::npos)
        {
            check_root(*it, addr_index);
        }
        else if (it->find("autoindex") != std::string::npos)
        {
            check_autoindex(*it, addr_index);
        }
        else if (it->find("error_page") != std::string::npos)
        {
            check_error_page(*it, addr_index);
        }
        else if (it->find("location") != std::string::npos)
        {
            check_location(*it, addr_index);
        }
        else if (it->find("accepted_method") != std::string::npos)
        {
            check_accepted_method(*it, addr_index);
        }
        else if (it->find("cgi_path") != std::string::npos)
        {
            check_cgi_path(*it, addr_index);
        }
        else if (it->find("upload_path") != std::string::npos)
        {
            check_upload_path(*it, addr_index);
        }
        else if (it->find("index") != std::string::npos)
        {
             check_index(*it, addr_index);
        }
        else if (it->find("return") != std::string::npos)
        {
            check_return(*it, addr_index);
        }
        else if (it->find("max_body_size") != std::string::npos)
        {
            check_max_body_size(*it, addr_index);
        }
        else
        {
            check_nothing(*it);
        }
  
    }

}

void create_vect_conf(const std::string &conf)
{
    /*fonction bonne qui met chaque ligne de la conf dans un vecteur*/
    std::vector<std::string> vect;
    std::istringstream input ; 
    input.str(conf) ; 
    for  ( std::string line ; std::getline( input, line) ;  )  { 
        vect.push_back(line); 
    }
    check_line_parsing(vect);       
}

/*******************************************************************/

std::string parsingName(const std::string &conf)
{
    size_t name_index = conf.find("server_name");
    if (name_index == std::string::npos)
        return (std::string());
    name_index = conf.find_first_not_of(" \t\n\r\v\f", name_index + 12);
    size_t name_length = conf.find(";", name_index);
    if (name_length == std::string::npos)
        throw confBadServerNameException();
    return (conf.substr(name_index, name_length - name_index));
}

std::string parsingRoot(const std::string &loc_conf, const Location &general)
{
    std::string root;
    size_t root_index = loc_conf.find("root"); 
    if (root_index == std::string::npos) // pas de directive root dans la loc
    {
        if (general.getRoot().empty())  // pas de directive root dans le server non plus
            return (getCurrentDirectory());
        return (general.getRoot());
    }
    root_index = loc_conf.find_first_not_of(" \t\n\r\v\f", root_index + 4);
    size_t root_end = loc_conf.find_first_of("; \t\n\r\v\f", root_index);
    if (root_end == std::string::npos)
        throw confInvalidRootException();
    return (getCurrentDirectory().append(loc_conf.substr(root_index, root_end - root_index)));
}

std::string  parsingIPAddress(const std::string &conf, unsigned int *ip, int *port)
{
    create_vect_conf(conf);
    
    size_t  addr_index = conf.find("listen");
    if (addr_index == std::string::npos)
        throw confNoListenException();
    addr_index = conf.find_first_not_of(" \t\n\r\v\f", addr_index + 7);
    *ip = convertIPAddress(conf, addr_index);
    size_t port_index = conf.find(":", addr_index);
    if (port_index == std::string::npos)
        throw confIPAddrException();
    port_index++;
    size_t port_length = conf.find(";", port_index);
    if (port_length == std::string::npos)
        throw confIPAddrException();
    *port = ft_atoi_parsing(conf.substr(port_index, port_length - port_index).c_str());
	if (*port < 0 || *port > 65535)
        throw confInvalidPortException();
    size_t i = conf.find('.');
    int a = 0;
    while(conf[i] != ':')
    {
        if (conf[i] == '.')
            a++;
        i++;
    }
    if (a > 3)
    {
        std::cout << "Error host" << std::endl;
        exit(EXIT_FAILURE);
    }
    return (conf.substr(addr_index, conf.find(':', addr_index) - addr_index));
}

void parsingLocations(std::list<Location*> &routes, const std::string &conf)
{
    size_t              last_found = conf.find("location");

    while (last_found < conf.size() && last_found < std::string::npos)
    {
        last_found += 9;
        size_t path_index = conf.find_first_not_of(" \t\n\r\v\f", last_found);
        size_t path_length = conf.find_first_of(" \t\n\r\v\f", path_index) - path_index;
        std::string path = conf.substr(path_index, path_length);
        std::string rules = getScope(conf, path_index + path_length);
        if (!rules.empty())
        {
            Location *to_push = new Location(path, rules, *routes.front());
            routes.push_back(to_push);
        }
        if ((last_found = conf.find("}", last_found)) != std::string::npos)
            last_found = conf.find("location", last_found);
    }
}

// ******************************************* //
// ***********  PARSING LOCATIONS  *********** //
// ******************************************* //

void     parsingAcceptedMethods(std::vector<int> &methods, const std::string &location_conf)
{
    size_t              index = location_conf.find("accepted_method");
    size_t              end = location_conf.find(';', index);

    if (index == std::string::npos || end == std::string::npos)
        return ;
    index += 15;
    while (index != end)
        methods.push_back(parseMethod(location_conf, &index));
}

std::list<std::string> parsingIndexes(const std::string &loc_conf, const Location &general)
{
    std::list<std::string>  indexes;
    size_t                  index_i = loc_conf.find("index");

    while (loc_conf.find("autoindex") == index_i - 4)
        index_i = loc_conf.find("index", index_i + 1);
    if (index_i == std::string::npos)
    {
        if (general.getIndexes().empty())
            indexes.push_front("index.html");
        else
            indexes = general.getIndexes();
        return (indexes);
    }
    index_i += 6;
    while (index_i < loc_conf.find(";", index_i) && index_i < std::string::npos)
    {
        size_t path_index = loc_conf.find_first_not_of(" \t\n\r\v\f", index_i);
        size_t path_length = loc_conf.find_first_of(" \t\n\r\v\f;", path_index) - path_index;
        indexes.push_back(loc_conf.substr(path_index, path_length));
        index_i = path_index + path_length;
    }
    return (indexes);
}

bool parsingAutoIndex(const std::string &loc_conf, const Location &general)
{
    size_t  index = loc_conf.find("autoindex");

    if (index == std::string::npos)
        return (general.getAutoIndex());
    index += 10;
    index = loc_conf.find_first_not_of(" \t\n\r\v\f", index);
    if (!loc_conf.compare(index, 2, "on"))
        return (true);
    return (false);
}

std::string    parsingCGIconf(const std::string &location_conf, const Location &general)
{
    size_t      index = location_conf.find("cgi_path");
    std::string cgi_path;
    struct stat statbuf;

    if (index == std::string::npos)
        return (general.getCGIPath());
    index += 9;
    index = location_conf.find_first_not_of(" \t\n\r\v\f", index);
    size_t end = location_conf.find(";", index);
    if (end == std::string::npos)
        throw confInvalidCGIException();
    cgi_path = location_conf.substr(index, end - index);
    // if (lstat(cgi_path.c_str(), &statbuf) == - 1)
    //     throw confInvalidCGIException();
    return (cgi_path);
}

size_t parsingBodySize(const std::string &loc_conf, const Location &general)
{
    size_t  index = loc_conf.find("max_body_size");
    size_t  max_body_size = 0;

    if (index == std::string::npos)
        return (general.getMaxBodySize());
    index += 14;
    index = loc_conf.find_first_not_of(" \t\n\r\v\f", index);
    size_t length = loc_conf.find_first_not_of("0123456789", index) - index;
    max_body_size = ft_atoul(loc_conf.substr(index, length));
    return (max_body_size);
}

std::map<int, std::string>    parsingErrorPage(const Location &location, const Location &general)
{
    struct stat statbuf;
    std::map<int, std::string> error_pages;
    size_t                      length;
    int                         code;
    std::string                 page_path;
    std::string location_conf = location.getConf();
    size_t      index = 0;

    while (1)
    {
        index = location_conf.find("error_page", index);
        if (index == std::string::npos)
            break ;
        index += 11;
        index = location_conf.find_first_not_of(" \t\n\r\v\f", index);
        // code 
        length = location_conf.find_first_not_of("0123456789", index) - index;
      //  std::cout << "lengit = " << length << std::endl;
		code = std::atoi(location_conf.substr(index, length).c_str());
        index += length;
        index = location_conf.find_first_not_of(" \t\n\r\v\f", index);
        // path
        size_t end = location_conf.find(";", index);
        if (end == std::string::npos)
            throw confInvalidErrorPageException();
        page_path = location_conf.substr(index, end - index);
	//	std::cout << "page error ? = " << page_path << std::endl;
        page_path.insert(0, location.getRoot() + "/");
        index += end - index;
        // if (lstat(page_path.c_str(), &statbuf) == - 1)
        // {
        //     std::cout << "stop" << std::endl;
        //     throw confInvalidErrorPageException();
        // }
        error_pages[code] = page_path;
    }
    if (error_pages.empty())
        return (general.getErrorPage());
    return (error_pages);
}

std::string parsingRedirection(const std::string &loc_conf, const Location &general)
{
    size_t          index = loc_conf.find("return");
    int             code;
    std::string     redirect_url;

    if (index == std::string::npos)
        return (general.getRedirectURL());
    index += 7;
    index = loc_conf.find_first_not_of(" \t\n\r\v\f", index);
    size_t length = loc_conf.find_first_not_of("0123456789", index) - index;
    code = std::atoi(loc_conf.substr(index, length).c_str());
    index += length;
    index = loc_conf.find_first_not_of(" \t\n\r\v\f", index);
    if (code == 301)
    {
        length = loc_conf.find(';', index) - index;
        return (loc_conf.substr(index, length));
    }
    return (general.getRedirectURL());
}

std::string parsingUploadPath(const std::string &loc_conf, const Location &general)
{
    size_t      index = loc_conf.find("upload_path");
    std::string upload_path;

    if (index == std::string::npos)
        return (general.getUploadPath());
    index += 12;
    index = loc_conf.find_first_not_of(" \t\n\r\v\f", index);
    size_t end = loc_conf.find(";", index);
    if (end == std::string::npos)
        throw confInvalidCGIException();
    upload_path = loc_conf.substr(index, end - index);
    return (upload_path);
}

// ******************************************** //
// ***********  HANDLING LOCATIONS  *********** //
// ******************************************** //


const Location &getRelevantLocation(const std::list<Location*> &_routes, const std::string &target)
{
    std::list<Location*>::const_iterator it = ++_routes.begin();
    std::string    loc = target;
    const Location *mostRelevant = (*(it));

    if (target.size() > 1 && target.find('/', 1) != std::string::npos)
        loc = loc.erase(target.find('/', 1));
    for (; it != _routes.end(); it++)
    {
        std::string     path = (*it)->getPath();
        size_t          size = path.size() > loc.size() ? path.size() : loc.size();
        if (!loc.compare(0, size, path) && (mostRelevant->getPath().size() < path.size()))
            mostRelevant = (*it);
    }
    return (*mostRelevant);
}

std::string buildPath(Server &server, Request &request, const std::string &target)
{  
    const Location  &loc = getRelevantLocation(server.getRoutes(), target);
    std::string     path(target);

    if (loc.getRootInConf() && loc.getPath().size() > 1)
    {
        if (path.find(loc.getPath()) != std::string::npos)
            path.erase(path.find(loc.getPath()), loc.getPath().size());
        if (path.empty())
            path = "/";
    }
    path.erase(path.find_last_of("/"), path.size() - path.find_last_of("/"));
    if (!loc.isAcceptedMethod(request.getMethodCode()))
        throw methodNotAllowedException();
    path.insert(0, loc.getRoot());
    if (loc.getPath().size() > 1)
    {
        if (path.find(loc.getPath()) != std::string::npos &&
            loc.getRoot().compare(server.getRoot()) != 0)
                path.erase(path.find(loc.getPath()), loc.getPath().size());
        if (request.getObject().find(&loc.getPath()[1]) != std::string::npos) // no '/' at the end
        {
            std::string tmp = request.getObject();
            if (loc.getRoot().compare(server.getRoot()) != 0)
                tmp.erase(tmp.find(&loc.getPath()[1]), loc.getPath().size() - 1);
            request.setObject(tmp);
        }
    }
    return (path);
}

const std::string firstValidIndex(const std::list<std::string> &indexes)
{
    struct stat     statbuf;

    for (std::list<std::string>::const_iterator it = indexes.begin(); it != indexes.end(); it++)
    {
        if (lstat((*it).c_str(), &statbuf) != -1)
            return (*it);
    }
    return (std::string());
}

const Location *findRootLocation(const std::list<Location*> &list)
{
    for (std::list<Location*>::const_iterator it = list.begin(); it != list.end(); it++)
    {
        if (!(*it)->getPath().compare("/"))
            return (*it);
    }
    return (NULL);
}
