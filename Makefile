#Detect OS
UNAME = `uname`

# Build based on OS name
DetectOS:
	-@make $(UNAME)

Linux:	./scripts/build_linux.sh
	chmod +x ./scripts/build_linux.sh
	./scripts/build_linux.sh

Windows_NT:	./scripts/build_windows.bat
	./scripts/build_windows.bat

