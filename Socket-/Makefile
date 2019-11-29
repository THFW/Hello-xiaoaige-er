.PHONY : clean service

GCC = gcc
object = service.o  client.o
LFLAG = -lpthread
#生成seevice.o的指令
service.o : 
	$(GCC) -c service.c -o service.o $(LFLAG)
#生成client.o的指令
client.o : 
	$(GCC) -c client.c -o client.o $(LFLAG)
#生成service执行文件的指令，先调用生成.o的指令
service : service.o  
	$(GCC) -o service service.o  $(LFLAG)
#生成client执行文件的指令，先调用生成.o的指令
client : client.o 
	$(GCC) -o client  client.o $(LFLAG)

all : client service
clean:
	rm $(object) service client