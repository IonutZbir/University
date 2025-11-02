package main

import (
	"fmt"
	"math/rand"
	"sched/algo"
	ds "sched/data_struct"
)

func main() {
	t := ds.NewTasks()
	for i := 0; i < 10; i++ {
		start := rand.Float32() * 50.0
		finish := rand.Float32() * 100.0
		if finish < start {
			c := start
			start = finish
			finish = c
		}
		t.Data = append(t.Data, *ds.NewTask(start, finish))
	}

	schedule := algo.IntervalPart(t)

	for i, sched := range schedule {
		fmt.Printf("Class: %v ", i)
		sched.ToString()
	}

}
