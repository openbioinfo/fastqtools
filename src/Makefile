
cc = g++
prom = fastqclean
deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -maxdepth 1  -name "*.cpp")
obj =  $(src:%.cpp=%.o)

$(prom) : $(obj)
	$(cc) -o ${prom} $(obj)

%.o : %.cpp $(deps)
	$(cc) -c $< -o $@


clean :
	rm -rf $(obj) ${prom}

