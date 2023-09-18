listing1.1:
	@mkdir -p build/cap1
	@gcc -o build/cap1/listing1.1  SRC/cap1/listing1.1.c SRC/cap1/listing1.2.cpp SRC/cap1/listing1.3.hpp

listing1.2:
	@mkdir -p build/cap1
	@gcc -o build/cap1/listing1.2  SRC/cap1/listing1.1.c SRC/cap1/listing1.2.cpp SRC/cap1/listing1.3.hpp

listing1.3:
	@mkdir -p build/cap1
	@gcc -o build/cap1/listing1.3  SRC/cap1/listing1.1.c SRC/cap1/listing1.2.cpp SRC/cap1/listing1.3.hpp


listing2.1:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.1  SRC/cap2/listing2.1.c 

listing2.2:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.2  SRC/cap2/listing2.2.c

listing2.3:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.3  SRC/cap2/listing2.3.c

listing2.4:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.4  SRC/cap2/listing2.4.c

listing2.5:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.5  SRC/cap2/listing2.5.c

listing2.6:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.6  SRC/cap2/listing2.6.c

listing2.7:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.7  SRC/cap2/listing2.8.c SRC/cap2/listing2.7.a

listing2.8:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.8  SRC/cap2/listing2.8.c SRC/cap2/listing2.7.a

listing2.9:
	@mkdir -p build/cap2
	@gcc -o build/cap2/listing2.9  SRC/cap2/listing2.9.c -ltiff


listing4.1:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.1  SRC/cap4/listing4.1.c

listing4.2:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.2  SRC/cap4/listing4.2.c

listing4.3:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.3  SRC/cap4/listing4.3.c

listing4.4:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.4  SRC/cap4/listing4.4.c



listing4.5:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.5  SRC/cap4/listing4.5.c


listing4.6:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.6  SRC/cap4/listing4.6.c

listing4.7:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.7  SRC/cap4/listing4.7.c

listing4.8:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.8  SRC/cap4/listing4.8.c

listing4.9:
	@mkdir -p build/cap4
	@g++ -o build/cap4/listing4.9  SRC/cap4/listing4.9.cpp




listing4.10:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.10  SRC/cap4/listing4.10.c


listing4.11:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.11  SRC/cap4/listing4.11.c


listing4.13:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.13  SRC/cap4/listing4.13.c

listing4.14:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.14  SRC/cap4/listing4.14.c
listing4.15:
	@mkdir -p build/cap4
	@gcc -o build/cap4/listing4.15  SRC/cap4/listing4.15.c

listing3.1:
	@mkdir -p build/cap3
	@gcc -o build/cap3/listing3.1  SRC/cap3/listing3.1.c
listing3.2:
	@mkdir -p build/cap3
	@gcc -o build/cap3/listing3.2  SRC/cap3/listing3.2.c
listing3.3:
	@mkdir -p build/cap3
	@gcc -o build/cap3/listing3.3  SRC/cap3/listing3.3.c
listing3.4:
	@mkdir -p build/cap3
	@gcc -o build/cap3/listing3.4  SRC/cap3/listing3.4.c
listing3.5:
	@mkdir -p build/cap3
	@gcc -o build/cap3/listing3.5  SRC/cap3/listing3.5.c
listing3.6:
	@mkdir -p build/cap3
	@gcc -o build/cap3/listing3.6  SRC/cap3/listing3.6.c

listing3.7:
	@mkdir -p build/cap3
	@gcc -o build/cap3/listing3.7  SRC/cap3/listing3.7.c









all: 
	@make listing1.1
	@make listing1.2
	@make listing1.3
	@make listing2.1
	@make listing2.2
	@make listing2.3
	@make listing2.4
	@make listing2.5
	@make listing2.6
	@make listing2.7
	@make listing2.8
	@make listing2.9
	@make listing4.1
	@make listing4.2
	@make listing4.3
	@make listing4.4
	@make listing4.5
	@make listing4.6
	@make listing4.7
	@make listing4.8
	@make listing4.9
	@make listing4.10
	@make listing4.11
	@make listing4.13
	@make listing4.14
	@make listing4.15
	@make listing3.1
	@make listing3.2
	@make listing3.3
	@make listing3.4
	@make listing3.5
	@make listing3.6
	@make listing3.7



	


	






clean: 
	@rm build -rf

.PHONY: clean all
