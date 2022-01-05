current_dir = $(shell pwd)

run:
	./bin/Debug/net6.0/Builder ./../../../Engine/

publish: clean
	dotnet publish -c release -r ubuntu.20.10-x64 --no-self-contained -o ./../bin


build:
	dotnet build

clean:
	rm -rf ./bin
	rm -rf ./obj
	rm -rf ./../bin