package main

import (
	_ "fmt"
)

type Node struct {
	Root *Node
	Val  int
}

type Set struct {
	Root *Node
	Size  int
}

type UnionFind struct {
	Data []Set
}

func NewNode(val int) *Node {
	return &Node{
		Root: nil,
		Val:  val,
	}
}

func NewSet(root *Node) *Set {
	return &Set{
		Root: root,
		Size:  1,
	}
}

func (uf *UnionFind) MakeSet(val int) {
	nd := NewNode(val)
	root := NewNode(val)
	nd.Root = root

	s := NewSet(root)
	uf.Data = append(uf.Data, *s)
}

func (uf *UnionFind) Find(nd *Node) *Set{
	return 
}

func (uf *UnionFind) Union(root1, root2 *Node)  {
	
}


