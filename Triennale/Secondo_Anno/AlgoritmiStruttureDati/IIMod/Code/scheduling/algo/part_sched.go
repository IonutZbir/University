package algo

import (
	"fmt"
	ds "sched/data_struct"
	"sort"
)

func IntervalPart(intervals *ds.Tasks) []ds.Tasks {
	schedule := make([]ds.Tasks, 0)
	pq := ds.NewDHeap(2)

	sort.Slice(intervals.Data, func(i, j int) bool {
		return intervals.Data[i].Start < intervals.Data[j].Start
	})

	tasks := intervals.Data
	length := len(tasks)

	pq.Insert(tasks[0].Finish, tasks[0])

	for i := 1; i < length; i++ {
		task := tasks[i]
		m := pq.FindMin().Key
		if task.Start >= m {
			delta := task.Finish - pq.Data[0].Key
			pq.Data[0].Val.Data = append(pq.Data[0].Val.Data, task)
			pq.IncreaseKey(0, delta)
		} else {
			pq.Insert(task.Finish, task)
		}
	}

	pq.PrintTree()

	fmt.Println("------------------------")

	for i := 0; i < pq.HeapSize; i++ {
		nd := pq.Data[i]
		schedule = append(schedule, *ds.NewTasks())

		for j := 0; j < len(nd.Val.Data); j++ {
			schedule[i].Data = append(schedule[i].Data, nd.Val.Data[j])
		}
	}

	return schedule
}
