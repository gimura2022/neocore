# Permission to use, copy, modify, and/or distribute this software for
# any purpose with or without fee is hereby granted.
#
# THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL
# WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE
# FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
# DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
# AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT
# OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

# Makefile - build script for neocore

include config.mk

export CFLAGS	+= -D'NEOCORE_VERSION="$(VERSION)"' -fPIC
export CPPFLAGS	+= -I$(shell realpath libneocore/include)
export LDFLAGS	+= -L$(shell realpath libneocore/) -lneocore

DESTDIR ?= /
PREFIX ?= usr/local

SUBDIRS :=	libneocore	\
		true		\
		false		\
		uname		\
		wc

.PHONY: all
all: $(SUBDIRS)

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ all

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done

define install_subdirs
	for dir in $(SUBDIRS); do $(MAKE) DESTDIR=$(shell realpath $(DESTDIR))/ PREFIX=$(PREFIX) -C $$dir $(1); done
endef

.PHONY: install
install:
	$(call install_subdirs, $@)

.PHONY: uninstall
uninstall:
	$(call install_subdirs, $@)
