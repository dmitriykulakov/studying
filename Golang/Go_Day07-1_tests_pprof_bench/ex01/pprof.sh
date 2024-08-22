go test ./tests -cpuprofile cpu.prof -count=100 -bench .
go tool pprof cpu.prof 
# top10 > top10.txt