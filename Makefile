PROJECTS := Core Tests
FORWARDED := clean help ${PROJECTS}

ifeq ($(shell uname -m),x86_64)
	platform := x64
else
	platform := x32
endif

config := debug
premake_config = ${config}_${platform}

.PHONY: all tests $(FORWARDED)

all: Build/projects
	$(MAKE) -C Build/projects all config=${premake_config}

tests: all
	Build/lib/${platform}/Tests

Build/projects:
	cd Build && ./MakeGMakeProjects.sh

$(PROJECTS): Build/projects
	$(MAKE) -C Build/projects $@ config=${premake_config}

