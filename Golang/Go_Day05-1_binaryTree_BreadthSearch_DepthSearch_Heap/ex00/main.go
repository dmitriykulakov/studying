package main

import (
	"fmt"
)

type TreeNode struct {
	HasToy bool
	Left   *TreeNode
	Right  *TreeNode
}

func areToysBalanced(Node *TreeNode) bool {
	var (
		leftCount  int = 0
		rightCount int = 0
	)
	leftCount = count(Node.Left)
	rightCount = count(Node.Right)
	return leftCount == rightCount
}

func count(Node *TreeNode) int {
	if Node != nil {
		if Node.HasToy {
			return 1 + count(Node.Left) + count(Node.Right)
		} else {
			return count(Node.Left) + count(Node.Right)
		}
	} else {
		return 0
	}

}

func CreateNode(v bool) *TreeNode {
	return &TreeNode{v, nil, nil}
}

func main() {
	Tree_1 := CreateNode(false)
	Tree_1.Left = CreateNode(false)
	Tree_1.Right = CreateNode(true)
	Tree_1.Left.Left = CreateNode(false)
	Tree_1.Left.Right = CreateNode(true)
	//     0
	//    / \
	//   0   1
	//  / \
	// 0   1
	Tree_2 := CreateNode(true)
	Tree_2.Left = CreateNode(true)
	Tree_2.Right = CreateNode(false)
	Tree_2.Left.Left = CreateNode(true)
	Tree_2.Left.Right = CreateNode(false)
	Tree_2.Right.Left = CreateNode(true)
	Tree_2.Right.Right = CreateNode(true)
	//      1
	//    /   \
	//   1     0
	//  / \   / \
	// 1   0 1   1
	Tree_3 := CreateNode(true)
	Tree_3.Left = CreateNode(true)
	Tree_3.Right = CreateNode(false)
	//    1
	//   / \
	//  1   0
	Tree_4 := CreateNode(false)
	Tree_4.Left = CreateNode(true)
	Tree_4.Right = CreateNode(false)
	Tree_4.Left.Right = CreateNode(true)
	Tree_4.Right.Right = CreateNode(true)
	//      0
	//    /   \
	//   1     0
	//    \     \
	//     1     1
	fmt.Println(areToysBalanced(Tree_1))
	fmt.Println(areToysBalanced(Tree_2))
	fmt.Println(areToysBalanced(Tree_3))
	fmt.Println(areToysBalanced(Tree_4))
}
