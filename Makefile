NB_THREADS=1
N=10
OUT=test_tmp
IN=test

all: seq

gentest:
	@bash test_generator.sh $(N) $(OUT)
	@cat $(OUT)

cc-seq:
	@gcc d2s.c -o seq -fopenmp 

seq: cc-seq $(IN)
	@./seq < $(IN)

cc-para:
	@gcc d2p.c -o para -fopenmp

para: cc-para $(IN)
	@cat $(IN)
	@./para < $(IN)

para-rand: cc-para gentest
	@./para < $(OUT)
clean:
	@rm -rf seq para *~
