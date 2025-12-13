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

# Makefile - build script for libneocore

OBJS :=	err.o	\
	rt.o

.PHONY: all
all: libneocore.a libneocore.so

libneocore.a: $(OBJS)
	$(AR) -rcs $@ $(OBJS)

libneocore.so: $(OBJS)
	$(CC) -o $@ $(OBJS) -shared

.PHONY: clean
clean:
	$(RM) $(OBJS)
	$(RM) libneocore.a
	$(RM) libneocore.so
