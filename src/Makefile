SUBDIRS:=$(wildcard */.)

.PHONY:all
all: $(SUBDIRS)

.PHONY:$(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)
	
.PHONY: clean
clean: $(SUBDIRS)
