project_name = GraphApp

scr_dir = ./sources/
hea_dir = ./headers/
obj_dir = ./objects/
bin_dir = ./binaries/

compiler = gcc
flags = -pedantic -Wall -W -I.

all: objects_folder binaries_folder $(project_name)

#Linkedição

$(project_name): $(obj_dir)test.o $(obj_dir)graph.o $(obj_dir)dijkstra.o
	@echo 'Constuindo binário utilizando gcc linker: $@'
	$(compiler) $^ -o $@
	@mv $(project_name) $(bin_dir)
	@echo ' '

#Compilação

$(obj_dir)graph.o : $(scr_dir)graph.c $(hea_dir)graph.h
	@echo "Construindo arquivos objetos utilizando gcc compiler: $@"
	$(compiler) -c $(flags) -o $@ $<
	@echo ' '

$(obj_dir)dijkstra.o : $(scr_dir)dijkstra.c $(hea_dir)dijkstra.h $(hea_dir)graph.h
	@echo "Construindo arquivos objetos utilizando gcc compiler: $@"
	$(compiler) -c $(flags) -o $@ $<
	@echo ' '

$(obj_dir)test.o : $(scr_dir)test.c $(hea_dir)graph.h $(hea_dir)dijkstra.h
	@echo "Construindo arquivos objetos utilizando gcc compiler: $@"
	$(compiler) -c $(flags) -o $@ $<
	@echo ' '

objects_folder:
	@mkdir -p objects

binaries_folder:
	@mkdir -p binaries

clean:
	@ rm -rf ./objects/*.o 
	@ rm -rf ./binaries/$(project_name) *~

	@ rmdir objects binaries

.PHONY: all clean