package algo

import (
	ds "sched/data_struct"
	"sort"
)

func IntervalScheduling(intervals *ds.Tasks) ds.Tasks {

	// Ordino per finish time
	sort.Slice(intervals.Data, func(i, j int) bool {
		return intervals.Data[i].Finish < intervals.Data[j].Finish
	})

	length := len(intervals.Data)
	schedule := ds.NewTasks()
	tasks := intervals.Data
	last := 0

	intervals.ToString()

	schedule.Data = append(schedule.Data, tasks[last])

	for i := 1; i < length; i++ {
		if tasks[i].IsCompatible(tasks[last]) {
			schedule.Data = append(schedule.Data, tasks[i])
			last = i
		}
	}
	return *schedule
}
