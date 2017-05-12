#include <stdio.h>  // printf
#include <stdarg.h> // va_start
#include <stdlib.h> // exit
#include <sys/stat.h> // stat
#include <string> // std::string
#include <list>
#include <map>

struct ResourceInfo {
	std::string fileName;
	std::string arrayName;
	unsigned int arraySize;
};

std::list<ResourceInfo> resource_list;

void help(const char* self_name)
{
  printf(
		"Утилита %s предназначена для \"компиляции\" ресурсов.\n"
		"Использование:\n"
		"%s <имя выходного заголовочного файла .h> [<имя файла-ресурса>[, ... ]]",
		self_name,
		self_name
	);
}

void error(int error, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf (stderr, format, args);
  va_end(args);

  exit(error);
}

void write_rc_header(FILE* rcf)
{
  fprintf(
    rcf,
		"#ifndef COMPILED_RESOURCES_H\n"
		"#define COMPILED_RESOURCES_H\n"
    "/////////////////////////////////////////////////////////////////////////////\n"
    "/// Compiled resources\n"
    "/////////////////////////////////////////////////////////////////////////////\n"
		"#include <map>\n"
		"#include <string>\n"
		"\n"
    );
}

void write_rc_footer(FILE* rcf)
{
  fprintf(
    rcf,
    "/////////////////////////////////////////////////////////////////////////////\n"
    "/// Compiled resources (end)\n"
    "/////////////////////////////////////////////////////////////////////////////\n"
		"#endif /* COMPILED_RESOURCES_H */\n"
    );
}

std::string string_replace_all_char(
  const std::string& source,
  const std::string& find,
  const std::string& replace)
{
  std::string result(source);

	unsigned int npp = 0;
	for(auto& fc : find) 
	{
			auto& rc = replace[npp % replace.size()];
			std::replace(result.begin(), result.end(), fc, rc);
			npp++;
	}

  return result;
}

void process_file(FILE* rcf, const char* file)
{
	struct stat sb;
	if (stat(file, &sb) == -1) return; // file exist ?
	if(sb.st_size == 0) return; // file with zero size
	
  FILE* res = fopen(file, "rb");
  if(!res) return; //  error(1, "Can't open resource file: |%s|", file);	

  std::string variable_name = string_replace_all_char(file, ".\\/ $#%&*+-@!","_");

  fprintf(
    rcf,
    "static const unsigned char\n\t%s[] = \n{\n\t",
    variable_name.c_str()
    );
		
	int c;
	unsigned int npp = 0;
	while((c=fgetc(res))!=EOF)
	{
			fprintf(rcf, "0x%02x, ", (unsigned char)c);
			npp++;
			if(npp % 12 == 0) fputc('\n', rcf),fputc('\t', rcf);
	}
	if(npp % 12) fputc('\n', rcf);

  fprintf(rcf, "};\n\n");
	
	ResourceInfo ri = {file, variable_name, npp};
	resource_list.push_back(ri);

  fclose(res);
}

int main(int argc, const char* argv[])
{
  if(argc < 2) return help(argv[0]),0;

  FILE* rcf = fopen(argv[1], "w+");
  if(!rcf) error(1, "Can't open output file: %s", argv[1]);
  write_rc_header(rcf);

	if (argc > 2)
	{
		/// читаем имена файлов-ресурсов из командной строки
		for (int i = 2; i < argc; ++i)
	  {
			printf("%s\n", argv[i]);
	    process_file(rcf, argv[i]);
	  }		
	}
	else
	{
		/// читаем имена файлов-ресурсов из stdin
		char *line = NULL;
		size_t linecap = 0;
		ssize_t linelen;
		while((linelen = getline(&line, &linecap, stdin)) > 0)
		{
			if(line[linelen-1] == '\n') line[linelen-1] = 0;
			printf("%s\n", line);			
			process_file(rcf, line);
			if(feof(stdin)) break;
		}		
	}
	
	fprintf(rcf, "static const\nstd::map<std::string, std::pair<const unsigned char*, unsigned int>>\n\tresources =\n{\n");
	for(auto& ri : resource_list) 
	{
			fprintf(
				rcf, 
				"\t{\":%s\", {%s, %d}},\n", 
				ri.fileName.c_str(),
				ri.arrayName.c_str(),
				ri.arraySize
			);
	}
	fprintf(rcf, "};\n\n");	

  write_rc_footer(rcf);
  fclose(rcf);

  return 0;
}
