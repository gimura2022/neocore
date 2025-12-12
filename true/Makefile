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

# Makefile - build script for true

DESTDIR ?= /

.PHONY: all
all: true

.PHONY: clean
clean:
	$(RM) true

.PHONY: install
install: all
	install -d $(DESTDIR)/bin/
	install -m 775 true $(DESTDIR)/bin/
	install -d $(DESTDIR)/share/man/man1/
	install -m 644 true.1 $(DESTDIR)/share/man/man1/

.PHONY: uninstall
uninstall:
	$(RM) $(DESTDIR)/bin/true
	$(RM) $(DESTDIR)/share/man/man1/true.1
