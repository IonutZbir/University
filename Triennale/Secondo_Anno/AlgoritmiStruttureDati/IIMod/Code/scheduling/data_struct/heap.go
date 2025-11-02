package data_struct

import (
	"fmt"
	"os"
)

type Node struct {
	Key float32
	Val Tasks
}

type DHeap struct {
	Data     []Node
	Type     int
	HeapSize int
}

func NewNode(key float32) *Node {
	return &Node{
		Key: key,
		Val: *NewTasks(),
	}
}

func NewDHeap(tp int) *DHeap {
	return &DHeap{
		Data:     make([]Node, 0),
		Type:     tp,
		HeapSize: 0,
	}
}

func (h *DHeap) swap(i, j int) {
	h.Data[i], h.Data[j] = h.Data[j], h.Data[i]
}

func (h *DHeap) minChild(nd int) int {
	minC := 0
	for i := 0; i < h.Type; i++ {
		j := h.Child(nd, i)
		if j < 0 {
			return -1
		}
		if h.Data[minC].Key > h.Data[j].Key {
			minC = j
		}
	}
	return minC
}

func (h *DHeap) Child(i, j int) int {
	// return the jth child of i
	k := (h.Type * i) + j + 1
	if k < h.HeapSize {
		return k
	}
	return -1
}

func (h *DHeap) Parent(i int) int {
	return (i - 1) / h.Type
}

func (h *DHeap) MoveHigh(index int) {
	if index >= h.HeapSize {
		fmt.Printf("[Error]: {%v > %v}, DHeap.MoveHigh()\n", index, h.HeapSize)
		os.Exit(1)
	}
	for i := index; i >= 0; i-- {
		nd := h.Data[i]
		j := h.Parent(i)
		parent := h.Data[j]

		if nd.Key < parent.Key {
			h.swap(i, j)
		}
	}
}

func (h *DHeap) MoveDown(index int) {
	if index >= h.HeapSize {
		fmt.Printf("[Error]: {%v > %v}, DHeap.MoveDown()\n", index, h.HeapSize)
		os.Exit(1)
	}
	for i := index; i < h.HeapSize; i++ {
		minC := h.minChild(i)
		if minC >= 0 && h.Data[minC].Key < h.Data[i].Key {
			h.swap(i, minC)
		}
	}
}

func (h *DHeap) FindMin() *Node {
	if h.HeapSize > 0 {
		return &h.Data[0]
	}
	return nil
}

func (h *DHeap) Insert(key float32, val Task) {
	nd := NewNode(key)
	nd.Val.Data = append(nd.Val.Data, val)
	h.Data = append(h.Data, *nd)
	h.HeapSize++
	h.MoveHigh(h.HeapSize - 1)
}

func (h *DHeap) Delete(index int) {
	if index >= h.HeapSize {
		fmt.Printf("[Error]: {%v > %v}, DHeap.Delete()\n", index, h.HeapSize)
		os.Exit(1)
	}
	h.swap(index, h.HeapSize-1)
	h.HeapSize--
	h.MoveDown(index)
	h.MoveHigh(index)
}

func (h *DHeap) DeleteMin() {
	h.Delete(0)
}

func (h *DHeap) IncreaseKey(index int, delta float32) {
	if index >= h.HeapSize {
		fmt.Printf("[Error]: {%v > %v}, DHeap.IncreaseKey()\n", index, h.HeapSize)
		os.Exit(1)
	}
	nd := &h.Data[index]
	nd.Key = nd.Key + delta
	h.MoveDown(index)
}

func (h *DHeap) DecreaseKey(index int, delta float32) {
	if index >= h.HeapSize {
		fmt.Printf("[Error]: {%v > %v}, DHeap.DecreaseKey()\n", index, h.HeapSize)
		os.Exit(1)
	}
	nd := &h.Data[index]
	nd.Key = nd.Key - delta
	h.MoveHigh(index)
}

func (nd *Node) ToString() { // public
	nd.toString("", "\n")
}

func (nd *Node) toString(indent, end string) { // private
	fmt.Printf("%s(Key: %v, Val: %v)%s", indent, nd.Key, nd.Val, end)
}

func (h *DHeap) ToString() {
	fmt.Printf("[")
	i := 0
	for ; i < h.HeapSize-1; i++ {
		h.Data[i].toString("", ",")
	}
	h.Data[i].toString("", "\n")
}

func (h *DHeap) PrintTree() { // public
	fmt.Printf("%v - Heap:\n", h.Type)
	h.printTree(0, 0)
}

func (h DHeap) printTree(level, node int) { // private
	if node > h.HeapSize {
		return
	}

	nd := h.Data[node]
	indent := getIndentation(level)
	nd.toString(indent, "\n")
	for i := 0; i < h.Type; i++ {
		child := h.Child(node, i)
		if child < 0 {
			return
		}
		h.printTree(level+1, child)
	}
}

func getIndentation(indent int) string {
	byteSlice := make([]byte, indent*4)
	for i := range byteSlice {
		byteSlice[i] = ' '
	}
	str := string(byteSlice)
	return str
}
