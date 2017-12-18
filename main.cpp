/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.cpp                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aberneli <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/18 16:48:56 by aberneli     #+#   ##    ##    #+#       */
/*   Updated: 2017/12/18 19:36:33 by aberneli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>

using namespace std;

void	usage()
{
	cout<<"Usage: PATH, NAME, CC, FLAGS"<<endl;
}

string	get_srcplist(string path)
{
	string		res;
	string		buf;
	string		tmp;
	ifstream	file;

	res = "";
	tmp = "ls -1 " + path + "*.cpp | rev | cut -d \"/\" -f 1 | rev > cpp.mg";
	system(tmp.c_str());
	file.open("./cpp.mg");
	while (file)
	{
		getline(file, buf);
		res += buf + " ";
	}
	res = res.substr(0, res.size() - 2);
	file.close();
	remove("./cpp.mg");
	return (res);
}


string	get_srclist(string path)
{
	string		res;
	string		buf;
	string		tmp;
	ifstream	file;

	res = "";
	tmp = "ls -1 " + path + "*.c | rev | cut -d \"/\" -f 1 | rev > c.mg";
	system(tmp.c_str());
	file.open("./c.mg");
	while (file)
	{
		getline(file, buf);
		res += buf + " ";
	}
	res = res.substr(0, res.size() - 2);
	file.close();
	remove("./c.mg");
	return (res);
}

string	get_headlist(string path)
{
	string		res;
	string		buf;
	string		tmp;
	ifstream	file;

	res = "";
	tmp = "ls -1 " + path + "*.h | rev | cut -d \"/\" -f 1 | rev > h.mg";
	system(tmp.c_str());
	file.open("./h.mg");
	while (file)
	{
		getline(file, buf);
		res += buf + " ";
	}
	res = res.substr(0, res.size() - 2);
	file.close();
	remove("./h.mg");
	return (res);
}


void	create_makefile(string path, char **argv)
{
	ofstream	file;
	int			i;
	string		tmp;

	i = 5;
	file.open(path);
	file<<".PHONY: all re clean fclean normy"<<endl<<endl;
	file<<"NAME = "<<argv[2]<<endl;
	if (strstr(argv[3], "ar") == argv[3])
	{
		file<<"AR = ar rcs"<<endl;
		file<<"CC = gcc"<<endl;
	}
	else
		file<<"CC = "<<argv[3]<<endl;
	file<<"FLAGS = "<<argv[4]<<endl;
	if (strstr(argv[3], "g++") == argv[3])
	{
		file<<"SRCS = "<<get_srcplist(argv[1])<<endl;
		file<<"OBJS = $(SRCS:.cpp=.o)"<<endl;
	}
	else
	{
		file<<"SRCS = "<<get_srclist(argv[1])<<endl;
		file<<"OBJS = $(SRCS:.c=.o)"<<endl;
	}
	file<<"HEADER = "<<get_headlist(argv[1])<<endl<<endl;
	file<<"all: $(NAME)"<<endl<<endl;
	file<<"$(NAME): $(OBJS)"<<endl;
	if (strstr(argv[3], "ar") == argv[3])
		file<<"	$(AR) $(NAME) $(OBJS)"<<endl<<endl;
	else
		file<<"	$(CC) $(FLAGS) $(OBJS) -o $(NAME)"<<endl<<endl;
	file<<"./%.o: ./%.c $(HEADERS)"<<endl;
	file<<"	$(CC) $(FLAGS) -o $@ -c $<"<<endl<<endl;
	file<<"clean:"<<endl;
	file<<"	rm -f $(OBJS)"<<endl<<endl;
	file<<"fclean: clean"<<endl;
	file<<"	rm -f $(NAME)"<<endl<<endl;
	file<<"re: fclean all"<<endl<<endl;
	file<<"normy:"<<endl;
	file<<"	norminette $(SRCS) $(HEADERS)"<<endl;
	file.close();
	tmp = "find ";
	tmp += argv[1];
	tmp += " -name \"Makefile\" -exec vim {} -c \"Stdheader\" -c \"wq\" \\;";
	system(tmp.c_str());
}

int		main(int argc, char **argv)
{
	ofstream	file;
	string		path;

	if (argc != 5)
	{
		usage();
		return (0);
	}
	path = argv[1];
	path += "Makefile";
	create_makefile(path, argv);
	return (0);
}
