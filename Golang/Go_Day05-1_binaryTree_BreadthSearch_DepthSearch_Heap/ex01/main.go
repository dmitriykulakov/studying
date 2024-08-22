package main

import (
	"fmt"
)

type TreeNode struct {
	HasToy bool
	Left   *TreeNode
	Right  *TreeNode
}

// func unrollGarland(Node *TreeNode) []bool {
// 	var result_slice []bool
// 	var result_tmp []int
// 	if Node != nil {
// 		result_unsorted := map[int]bool{1: Node.HasToy}
// 		addNode(&result_unsorted, 2, Node, 1)
// 		for id := range result_unsorted {
// 			result_tmp = append(result_tmp, id)
// 		}
// 		sort.Slice(result_tmp, func(i, j int) bool {
// 			return result_tmp[i] < result_tmp[j]
// 		})
// 		fmt.Println(result_unsorted)
// 		for i := 0; i < len(result_unsorted); i++ {
// 			result_slice = append(result_slice, result_unsorted[result_tmp[i]])
// 		}
// 	}
// 	return result_slice
// }

// func addNode(m *map[int]bool, line int, Node *TreeNode, Number int) {
// 	id := int(math.Pow(2, float64(line))*1.5) - Number*2 - 1
// 	if Node.Left != nil {
// 		if line%2 == 0 {
// 			(*m)[Number*2] = Node.Left.HasToy
// 		} else {
// 			(*m)[id] = Node.Left.HasToy
// 		}
// 		addNode(m, line+1, Node.Left, Number*2)
// 	}
// 	if Node.Right != nil {
// 		if line%2 == 0 {
// 			(*m)[Number*2+1] = Node.Right.HasToy
// 		} else {
// 			(*m)[id-1] = Node.Right.HasToy
// 		}
// 		addNode(m, line+1, Node.Right, Number*2+1)
// 	}
// }

func unrollGarland(Node *TreeNode) []bool {
	var (
		leftRidhtWay bool = false
		result       []bool
		currentRow   []*TreeNode
		nextRow      []*TreeNode
	)
	nextRow = append(nextRow, Node)
	for len(nextRow) > 0 {
		currentRow = nil
		currentRow, nextRow = nextRow, currentRow
		for _, el := range currentRow {
			if el.Left != nil {
				nextRow = append(nextRow, el.Left)
			}
			if el.Right != nil {
				nextRow = append(nextRow, el.Right)
			}
		}
		if leftRidhtWay {
			for _, el := range currentRow {
				result = append(result, el.HasToy)
			}
			leftRidhtWay = false
		} else {
			for elNumber := len(currentRow) - 1; elNumber >= 0; elNumber-- {
				result = append(result, currentRow[elNumber].HasToy)
			}
			leftRidhtWay = true
		}
	}
	return result
}

func CreateNode(v bool) *TreeNode {
	return &TreeNode{v, nil, nil}
}

func main() {
	Tree_1 := CreateNode(true)
	Tree_1.Left = CreateNode(true)
	Tree_1.Right = CreateNode(false)
	Tree_1.Left.Left = CreateNode(true)
	Tree_1.Left.Right = CreateNode(false)
	Tree_1.Right.Left = CreateNode(true)
	Tree_1.Right.Right = CreateNode(true)
	Tree_1.Left.Left.Left = CreateNode(false)
	Tree_1.Right.Right.Right = CreateNode(true)
	Tree_1.Right.Right.Right.Left = CreateNode(false)
	Tree_1.Right.Right.Right.Right = CreateNode(true)
	//       1
	//     /   \
	//    1     0
	//   / \   / \
	//  1   0 1   1
	//   \         \
	//    0         1
	//             / \
	//            0   1
	fmt.Println(unrollGarland(Tree_1))

}
