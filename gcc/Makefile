makefile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
makefile_dir := $(dir $(makefile_path))


.PHONY: all clean assets flash intflash

all clean  assets flash intflash:
	$(MAKE) -C $(makefile_dir) --no-print-directory -f makefile_boot $(MAKEFLAGS) $@
	$(MAKE) -C $(makefile_dir) --no-print-directory -f makefile_appli $(MAKEFLAGS) $@