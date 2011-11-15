#-lgc -ggdb
SRC_DIR="src"
all:
	@cd ${SRC_DIR}; make
.PHONY:	clean
clean:
	@cd ${SRC_DIR}; make clean
tar:
	@cd ${SRC_DIR}; make tar
