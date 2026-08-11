DEFAULT_HOST!=../default-host.sh
HOST?=DEFAULT_HOST
HOSTARCH!=../target-triplet-to-arch.sh $(HOST)

CFLAGS?=-O0 -g
CPPFLAGS?= 
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

BUILDDIR?=../build/kernel

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

ARCHDIR=arch/$(HOSTARCH)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) \
kernel/eventqueue.o \
kernel/kernel.o \
kernel/cbuffer.o \
kernel/shell.o \
kernel/command.o\
kernel/commands/version.o \
kernel/commands/tty_commands.o \
kernel/pmm/pmm.o \
kernel/pmm/pmm_tests.o \


OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

BOBJS=$(addprefix $(BUILDDIR)/,$(OBJS))
BKERNEL_OBJS=$(addprefix $(BUILDDIR)/,$(KERNEL_OBJS))

LINK_LIST=\
$(LDFLAGS) \
$(BUILDDIR)/$(ARCHDIR)/crti.o \
$(BUILDDIR)/$(ARCHDIR)/crtbegin.o \
$(BKERNEL_OBJS) \
$(LIBS) \
$(BUILDDIR)/$(ARCHDIR)/crtend.o \
$(BUILDDIR)/$(ARCHDIR)/crtn.o \

.PHONY: all clean install install-headers install-kernel

all: $(BUILDDIR)/zenos.kernel

$(BUILDDIR)/zenos.kernel: $(BOBJS) $(ARCHDIR)/linker.ld
	@mkdir -p $(@D)
	$(CC) -T $(ARCHDIR)/linker.ld -Wl,-Map,$(BUILDDIR)/zenos.map -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot $@

$(BUILDDIR)/$(ARCHDIR)/crtbegin.o $(BUILDDIR)/$(ARCHDIR)/crtend.o:
	@mkdir -p $(@D)
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) -MD -c  $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

$(BUILDDIR)/%.o: %.S
	@mkdir -p $(@D)
	$(CC) -MD -c  $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -rf $(BUILDDIR)

install: install-headers install-kernel

install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.

install-kernel: $(BUILDDIR)/zenos.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp $(BUILDDIR)/zenos.kernel $(DESTDIR)$(BOOTDIR)

-include $(BOBJS:.o=.d)
