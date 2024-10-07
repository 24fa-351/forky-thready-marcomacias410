fork: fork.c
	gcc -o fork fork.c

results: fork
	(echo "Pattern 1:"; ./fork 1 $$((RANDOM % 15 + 5)); \
	echo; \
	echo "Pattern 2:"; ./fork 2 $$((RANDOM % 15 + 5)); \
	echo; \
	echo "Pattern 3:"; ./fork 3 $$((RANDOM % 20 + 5))) \
		> fortnite.txt 2>&1

clean:
	rm -f fork
