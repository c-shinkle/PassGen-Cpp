run:
	./bin/pass_gen

release:
	clang++ main.cpp -std=c++2a -Ofast -o bin/pass_gen

debug:
	clang++ main.cpp -std=c++2a -g -o bin/pass_gen

clean:
	rm -r bin/pass_gen

copy: release
	cp ./bin/pass_gen ~/Coding/Hyperfine/C++
