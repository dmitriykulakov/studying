go test ./tests -bench=. -count=100 > new.txt
go test ./tests -bench=. -count=100 > old.txt
benchstat old.txt new.txt