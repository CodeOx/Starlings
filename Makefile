CC = g++
LINK_TARGET = test.exe
ODIR = obj

OBJS = \
	Swarm.o \
	Vector.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)
_OBJS = $(patsubst %,$(ODIR)/%,$(OBJS))

all :	$(LINK_TARGET)
	echo	all	done


$(LINK_TARGET) :	$(_OBJS)
#$(LINK_TARGET) : $(OBJS)
#	$(CC)	-o	$@ main.cpp	$^

$(ODIR)/%.o:%.cpp
	$(CC)	-c	-o	$@	$<

.PHONY:	clean

clean:
	rm	-f	$(ODIR)/*.o	$(OUT)