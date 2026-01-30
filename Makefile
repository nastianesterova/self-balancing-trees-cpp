#
# Mark's Magic Makefile
#
# Instructions:
#
# 1. Add .cpp files (not .h files) to the line beginning with SRCS = main.cpp.
#    Files should be separated with spaces, not commas.  If all of the
#    .cpp files in the directory should be included in the build, then you
#    can avoid maintaining a specific list of source files by commenting
#    out the first SRCS line and uncommenting the second.
# 2. Type 'make depend' to build or update the dependency list.  Do this
#    whenever you add this Makefile or add a .cpp or .h file to a project.
# 3. Type 'make' to build the project.
# 4. Type 'make clean' to start over or prepare for submission.  This does
#    not remove the dependency information.
#
# N.B. If you're using files with .cc extensions, then you need to search
# and replace cpp with cc.
#

CC = g++
CFLAGS = -std=c++11 -Wall -g
# For this project, you'll have only main.cpp, since we're using
# template classes.  Do not compile .h files.  See INCLS
SRCS = main.cpp
#SRCS = ${wildcard *.cpp}
OBJS = ${SRCS:.cpp=.o}
INCLS = ${SRCS:.cpp=.h} binary.h avl.h splay.h node.h DLnode.h

a.out: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o p2

$(OBJS):
	$(CC) $(CFLAGS) -c $*.cpp

depend: Makefile.dep
	$(CC) -MM $(SRCS) > Makefile.dep

Makefile.dep:
	touch Makefile.dep

.PHONY: submit clean

submit:
	rm -f submit.zip
	zip submit.zip $(SRCS) $(INCLS) HONOR Makefile Makefile.dep

clean:
	rm -f $(OBJS) a.out core p2

p1:
	make a.out

include Makefile.dep
