include config.mk

export CFLAGS += -D'NEOCORE_VERSION="$(VERSION)"'

export POSTFIX ?= usr/local
export DESTDIR ?= /

SUBDIRS :=	true

.PHONY: all
all: $(SUBDIRS)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ all

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done

.PHONY: install
install:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done

.PHONY: uninstall
uninstall:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done
