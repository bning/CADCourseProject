#include "ImagePreLim.h"

ImagePreLim::ImagePreLim(char *name) :
		ParamMap(name) {
	outputFolderName = getStringParam("outputFolderName");
	inputFolderName = getStringParam("inputFolderName");

	imageFileName = getStringParam("imageFileName");
	nRows = getIntParam("imageRows");
	nCols = getIntParam("imageCols");

	doSubDivide = getIntParam("doSubDivide");
	//testSubImageFileName = getStringParam("testSubImageFileName");
}

void ImagePreLim::SubDivide(vector<vector<Vertex> > &image,
		vector<Cell> &quadTree, int* cellCount) {
	list<Node> allElements;

	Node motherNode(0, 0, nRows, nCols);
	motherNode.nodeDepth = 0;

	queue<Node*> queueNodes;
	allElements.push_back(motherNode);
	Node* motherNodePtr = &allElements.back();
	queueNodes.push(motherNodePtr);

	while (!queueNodes.empty()) {
		Node* nextNode = queueNodes.front();
		//allElements.push_back(nextNode);
		queueNodes.pop();
		if (nextNode->nodeRows > 1 && nextNode->nodeCols > 1) {
			//cout << endl;
			//cout << "sR " << nextNode->startRow << " sC " << nextNode->startCol << endl;
			//cout << "sRows " << nextNode->nodeRows << " sCols " << nextNode->nodeCols << endl;
			if (nextNode->nodeDepth > 0) {
				//cout << "psR " << nextNode->parentNode->startRow << " psC " <<
				nextNode->parentNode->startCol;
				//cout << "pChildren " << nextNode->parentNode->noChildren << endl;
			}
			nextNode->SplitQuadNode(allElements, image, false);
			if (!nextNode->isLeafNode && nextNode->nodeDepth >= 2) {
				nextNode->RemoveHangingPoint(allElements, image);
			}
			if (nextNode->nodeDepth > 0) {
				if (nextNode->nodeOrder
						>= nextNode->parentNode->noChildren - 1) {
					nextNode->parentNode->CloseSiblingHangingPoint();
				}
			}
			for (int childInd = 0; childInd < nextNode->noChildren;
					childInd++) {
				queueNodes.push(nextNode->childrenNode.at(childInd));
			}
			/*cout << "parentNode check" << endl;

			 cout << "pop rows " << nextNode.nodeRows << endl;
			 cout << "pop cols " << nextNode.nodeCols << endl;
			 cout << "pop start row " << nextNode.startRow << endl;
			 cout << "pop start col " << nextNode.startCol << endl;

			 cout << "pop isleafnode " << nextNode.isLeafNode << endl;

			 if (!nextNode.isLeafNode)
			 {
			 cout << "parent rows " << nextNode.childrenNode.at(3).parentNode->nodeRows << endl;
			 cout << "parent cols " << nextNode.childrenNode.at(3).parentNode->nodeCols << endl;
			 cout << "parent start row " << nextNode.childrenNode.at(3).parentNode->startRow
			 << endl;
			 cout << "parent start col " << nextNode.childrenNode.at(3).parentNode->startCol
			 << endl;

			 cout << "child rows " << nextNode.childrenNode.at(3).nodeRows << endl;
			 cout << "child cols " << nextNode.childrenNode.at(3).nodeCols << endl;
			 cout << "child start row " << nextNode.childrenNode.at(3).startRow << endl;
			 cout << "child start col " << nextNode.childrenNode.at(3).startCol << endl;
			 }        */
		} else {
			nextNode->isLeafNode = true;
			nextNode->val =
					image.at(nextNode->startRow).at(nextNode->startCol).val;
		}
	}
	quadTree.resize(nRows * nCols);

	ConvertTreeToCellStructure(motherNodePtr, quadTree, cellCount);

	vector<int> subImage(nRows * nCols);
	cout << *cellCount << endl;
	TestCellIntoSubImage(quadTree, subImage, *cellCount);

	//WriteTestSubCSVImage(subImage, nCols, nRows, testSubImageFileName);
}

void Node::SplitQuadNode(list<Node> &allElements,
		vector<vector<Vertex> > &image, bool doSplit) {
	int endRow = startRow + nodeRows - 1;
	int endCol = startCol + nodeCols - 1;

	bool doContinue = true;
	int firstVal = image.at(startRow).at(startCol).val;
	int rowI = startRow;
	if (!doSplit) {
		while (doContinue && rowI <= endRow) {
			int colI = startCol;
			while (doContinue && colI <= endCol) {
				//cout << rowI << " " << colI << endl;
				if (image.at(rowI).at(colI).val != firstVal) {
					doContinue = false;
				}
				colI++;
			}
			rowI++;
		}
	}
	if (!doContinue || doSplit) {
		//order of children is 0, 1; 2, 3 (like raster scan)

		isLeafNode = false;
		int childrenCounter = 0;

		Node startCornerNode(startRow, startCol, nodeRows / 2, nodeCols / 2);
		startCornerNode.parentNode = this;
		startCornerNode.nodeOrder = 0;
		startCornerNode.nodeDepth = nodeDepth + 1;
		allElements.push_back(startCornerNode);
		childrenNode.push_back(&allElements.back());
		childrenCounter++;

		int nextStartCol = 0;
		int nextStartRow = 0;
		if (nodeCols > 1) {
			nextStartCol = startCol + nodeCols / 2;
			Node nextColNode(startRow, nextStartCol, nodeRows / 2,
					nodeCols / 2);
			nextColNode.parentNode = this;
			nextColNode.nodeOrder = 1;
			nextColNode.nodeDepth = nodeDepth + 1;
			allElements.push_back(nextColNode);
			childrenNode.push_back(&allElements.back());
			childrenCounter++;
		}
		if (nodeRows > 1) {
			nextStartRow = startRow + nodeRows / 2;
			Node nextRowNode(nextStartRow, startCol, nodeRows / 2,
					nodeCols / 2);
			nextRowNode.parentNode = this;
			nextRowNode.nodeOrder = 2;
			nextRowNode.nodeDepth = nodeDepth + 1;
			allElements.push_back(nextRowNode);
			childrenNode.push_back(&allElements.back());
			childrenCounter++;
		}
		if (nodeRows > 1 && nodeCols > 1) {
			Node nextBothNode(nextStartRow, nextStartCol, nodeRows / 2,
					nodeCols / 2);
			nextBothNode.parentNode = this;
			nextBothNode.nodeOrder = 3;
			nextBothNode.nodeDepth = nodeDepth + 1;
			allElements.push_back(nextBothNode);
			childrenNode.push_back(&allElements.back());
			childrenCounter++;
		}

		noChildren = childrenCounter;

		if (doSplit) {
			for (int ind = 0; ind < noChildren; ind++) {
				childrenNode.at(ind)->val = val;
				childrenNode.at(ind)->isLeafNode = true;
				childrenNode.at(ind)->noChildren = 0;
			}
		}
	} else {
		noChildren = 0;
		isLeafNode = true;
		val = firstVal;
		//cout << "LEAF " << val << endl;
	}
}

void Node::RemoveHangingPoint(list<Node> &allElements,
		vector<vector<Vertex> > &image) {
	int yCheck = nodeOrder / 2;
	if (yCheck == 0) {
		yCheck = -1;
	}
	int xCheck = nodeOrder % 2;
	if (xCheck == 0) {
		xCheck = -1;
	}
	/*int parentNodeOrder = parentNode->nodeOrder;
	 int parentRowOrder = parentNodeOrder/2;
	 int parentColOrder = parentNodeOrder%2;

	 int uncleIndices[2];
	 uncleIndices[0] = (parentRowOrder+yCheck)*2+parentColOrder;
	 uncleIndices[1] = parentRowOrder*2+(parentColOrder+xCheck);*/

	int yChange[2];
	yChange[0] = yCheck;
	yChange[1] = 0;
	int xChange[2];
	xChange[0] = 0;
	xChange[1] = xCheck;
	int yNewInd = 0;
	if (yCheck < 0) {
		yNewInd = 1;
	}
	int xNewInd = 0;
	if (xCheck < 0) {
		xNewInd = 1;
	}
	int yNewInds[2];
	yNewInds[0] = yNewInd;
	yNewInds[1] = -10;
	int xNewInds[2];
	xNewInds[0] = -10;
	xNewInds[1] = xNewInd;

	int yFixInds[2];
	yFixInds[0] = yNewInd;
	yFixInds[1] = -1;
	int xFixInds[2];
	xFixInds[0] = -1;
	xFixInds[1] = xNewInd;

	/*cout << endl;
	 cout << "check grand nochildren " << parentNode->parentNode->noChildren << endl;
	 cout << "check grand rows " << parentNode->parentNode->nodeRows << endl;
	 cout << "check grand cols " << parentNode->parentNode->nodeCols << endl;
	 cout << "check grand start row " << parentNode->parentNode->startRow << endl;
	 cout << "check grand start col " << parentNode->parentNode->startCol << endl;*/

	for (int uncleInd = 0; uncleInd < 2; uncleInd++) {
		int noGenerationsToJump = 2;
		vector<int> oldRowOrder(nodeDepth);
		vector<int> oldColOrder(nodeDepth);
		int saveGenerationChangeOrder = 0;
		Node* backNode = 0;
		while (noGenerationsToJump <= nodeDepth) {
			backNode = this;
			Node* lastButOneBackNode = 0;
			for (int generationI = 0; generationI < noGenerationsToJump;
					generationI++) {
				backNode = backNode->parentNode;
				if (generationI == noGenerationsToJump - 2) {
					lastButOneBackNode = backNode;
				}
				oldRowOrder.at(generationI) = backNode->nodeOrder / 2;
				oldColOrder.at(generationI) = backNode->nodeOrder % 2;
			}
			int lastButOneOrder = lastButOneBackNode->nodeOrder;
			int lastButOneRowOrder = lastButOneOrder / 2;
			int lastButOneColOrder = lastButOneOrder % 2;
			int generationChangeOrder = (lastButOneRowOrder + yChange[uncleInd])
					* 2 + (lastButOneColOrder + xChange[uncleInd]);
			if (generationChangeOrder >= 0
					&& generationChangeOrder < backNode->noChildren) {
				saveGenerationChangeOrder = generationChangeOrder;
				break;
			} else {
				noGenerationsToJump++;
			}
		}
		if (noGenerationsToJump <= nodeDepth) {
			//cout << "no generations " << noGenerationsToJump << endl;
			Node* changedOrder = backNode->childrenNode.at(
					saveGenerationChangeOrder);
			int generationIndex = noGenerationsToJump - 3; //count is minus 2 and index is count-1
			while (changedOrder->nodeDepth < nodeDepth - 1) {
				int newRowOrder = 0;
				int newColOrder = 0;
				if (yFixInds[uncleInd] == -1) {
					newRowOrder = oldRowOrder.at(generationIndex);
				} else {
					newRowOrder = yNewInds[uncleInd];
				}
				if (xFixInds[uncleInd] == -1) {
					newColOrder = oldColOrder.at(generationIndex);
				} else {
					newColOrder = xNewInds[uncleInd];
				}
				changedOrder = changedOrder->childrenNode.at(
						newRowOrder * 2 + newColOrder);

				generationIndex--;
			}
			if (changedOrder->isLeafNode) {
				changedOrder->SplitQuadNode(allElements, image, true);

				if (changedOrder->nodeDepth >= 2) {
					changedOrder->RemoveHangingPoint(allElements, image);
				}
			}
			// add hanging node information

			int finalNewRowOrder = 0;
			int finalNewColOrder = 0;
			if (yFixInds[uncleInd] == -1) {
				finalNewRowOrder = nodeOrder / 2;
			} else {
				finalNewRowOrder = yNewInds[uncleInd];
			}
			if (xFixInds[uncleInd] == -1) {
				finalNewColOrder = nodeOrder % 2;
			} else {
				finalNewColOrder = xNewInds[uncleInd];
			}
			Node* nodeWithHanging = changedOrder->childrenNode.at(
					finalNewRowOrder * 2 + finalNewColOrder);

			/*for (int ind = 0; ind < 4; ind++)
			 {
			 nodeWithHanging->isHanging[ind] = 0;
			 }*/
			if (yChange[uncleInd] < 0) {
				nodeWithHanging->isHanging[1] = 1;
			} else if (yChange[uncleInd] > 0) {
				nodeWithHanging->isHanging[3] = 1;
			} else {
				if (xChange[uncleInd] < 0) {
					nodeWithHanging->isHanging[2] = 1;
				} else if (xChange[uncleInd] > 0) {
					nodeWithHanging->isHanging[0] = 1;
				}
			}
		}

		/*if (uncleIndices[uncleInd] >= 0 && uncleIndices[uncleInd] <
		 (parentNode->parentNode)->noChildren)
		 {
		 cout << "if" << endl;
		 /*cout << "hero start row " << startRow << endl;
		 cout << "hero start col " << startCol << endl;
		 cout << "hero rows " << nodeRows << endl;
		 cout << "hero cols " << nodeCols << endl;
		 cout << endl;
		 cout << "grand parent rows " << parentNode->parentNode->nodeRows << endl;
		 cout << "grand parent cols " << parentNode->parentNode->nodeCols << endl;
		 cout << "grand parent start row " << parentNode->parentNode->startRow << endl;
		 cout << "grand parent start col " << parentNode->parentNode->startCol << endl;                                */
		/*if (parentNode->parentNode->childrenNode.at(uncleIndices[uncleInd])->isLeafNode)
		 {
		 parentNode->parentNode->childrenNode.at(uncleIndices[uncleInd])->SplitQuadNode(allElements,
		 image, true);

		 if (parentNode->parentNode->childrenNode.at(uncleIndices[uncleInd])->nodeDepth
		 >= 2)
		 {
		 parentNode->parentNode->childrenNode.at(uncleIndices[uncleInd])->RemoveHangingPoint(allElements,
		 image);
		 }
		 }
		 }
		 else
		 {
		 cout << "else" << endl;
		 if (nodeDepth >= 3)
		 {
		 int grandParentNodeOrder = parentNode->parentNode->nodeOrder;
		 int grandParentRowOrder = grandParentNodeOrder/2;
		 int grandParentColOrder = grandParentNodeOrder%2;
		 int grandParentChangeOrder =
		 (grandParentRowOrder+yChange[uncleInd])*2+(grandParentColOrder+xChange[uncleInd]);
		 if (grandParentChangeOrder >= 0 && grandParentChangeOrder <
		 parentNode->parentNode->parentNode->noChildren)
		 {
		 int orderFromGrandParent = yNewInds[uncleInd]*2+xNewInds[uncleInd];
		 cout << "hero start row " << startRow << endl;
		 cout << "hero start col " << startCol << endl;
		 cout << "hero rows " << nodeRows << endl;
		 cout << "hero cols " << nodeCols << endl;
		 cout << "oFGP " << orderFromGrandParent << endl;
		 cout << "check noChildren " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->noChildren
		 << endl;
		 cout << "startCol " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->startCol
		 << endl;
		 cout << "startRow " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->startRow
		 << endl;
		 cout << "cols " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->nodeCols
		 << endl;
		 cout << "rows " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->nodeRows
		 << endl;

		 cout << "isleaf test " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->isLeafNode
		 << endl;
		 cout << "node depth test " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->nodeDepth
		 << endl;
		 cout << "test children size " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.size()
		 << endl;

		 /*cout << "check grand nochildren " << parentNode->parentNode->noChildren << endl;
		 cout << "check grand rows " << parentNode->parentNode->nodeRows << endl;
		 cout << "check grand cols " << parentNode->parentNode->nodeCols << endl;
		 cout << "check grand start row " << parentNode->parentNode->startRow << endl;
		 cout << "check grand start col " << parentNode->parentNode->startCol << endl;

		 cout << "test child startCol " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.at(0)->startCol
		 << endl;
		 cout << "test child startRow " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.at(0)->startRow
		 << endl;
		 cout << "test child cols " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.at(0)->nodeCols
		 << endl;
		 cout << "test child rows " <<
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.at(0)->nodeRows
		 << endl;*/
		/*cout << "parent rows " << parentNode->nodeRows << endl;
		 cout << "parent cols " << parentNode->nodeCols << endl;
		 cout << "grand parent rows " << parentNode->parentNode->nodeRows << endl;
		 cout << "grand parent cols " << parentNode->parentNode->nodeCols << endl;
		 cout << "grand parent start row " << parentNode->parentNode->startRow << endl;
		 cout << "grand parent start col " << parentNode->parentNode->startCol << endl;*/
		/*if
		 (parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.at(orderFromGrandParent)->isLeafNode)
		 {
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.at(orderFromGrandParent)->SplitQuadNode(allElements,
		 image, true);

		 if
		 (parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.at(orderFromGrandParent)->nodeDepth
		 >= 2)
		 {
		 parentNode->parentNode->parentNode->childrenNode.at(grandParentChangeOrder)->childrenNode.at(orderFromGrandParent)->RemoveHangingPoint(allElements,
		 image);
		 }
		 }
		 }
		 }
		 }*/
	}
}

void Node::CloseSiblingHangingPoint() {
	for (int childI = 0; childI < noChildren; childI++) {
		if (!childrenNode.at(childI)->isLeafNode) {
			int childSplitOrder = childrenNode.at(childI)->nodeOrder;
			int childSplitRow = childSplitOrder / 2;
			int childSplitCol = childSplitOrder % 2;

			int otherSideSiblingRow = -1 * childSplitRow;
			int otherSideSiblingCol = -1 * childSplitCol;
			if (otherSideSiblingRow == 0) {
				otherSideSiblingRow = 1;
			}
			if (otherSideSiblingCol == 0) {
				otherSideSiblingCol = 1;
			}
			int siblingIndices[2];
			int yChange[2];
			yChange[0] = otherSideSiblingRow;
			yChange[1] = 0;
			int xChange[2];
			xChange[0] = 0;
			xChange[1] = otherSideSiblingCol;
			siblingIndices[0] = (childSplitRow + otherSideSiblingRow) * 2
					+ childSplitCol;
			siblingIndices[1] = childSplitRow * 2
					+ (childSplitCol + otherSideSiblingCol);

			for (int siblingI = 0; siblingI < 2; siblingI++) {
				if (childrenNode.at(siblingIndices[siblingI])->isLeafNode) {
					if (yChange[siblingI] < 0) {
						childrenNode.at(siblingIndices[siblingI])->isHanging[1] =
								1;
					} else if (yChange[siblingI] > 0) {
						childrenNode.at(siblingIndices[siblingI])->isHanging[3] =
								1;
					} else {
						if (xChange[siblingI] < 0) {
							childrenNode.at(siblingIndices[siblingI])->isHanging[2] =
									1;
						} else if (xChange[siblingI] > 0) {
							childrenNode.at(siblingIndices[siblingI])->isHanging[0] =
									1;
						}
					}
				}
			}
		}
	}
}

void ImagePreLim::ConvertTreeToCellStructure(Node* motherNode,
		vector<Cell> &quadTree, int* cellCount) {
	queue<Node*> queueNodes;
	queueNodes.push(motherNode);

	Node* nextNode = 0;

	int cellCounter = 0;

	while (!queueNodes.empty()) {
		nextNode = queueNodes.front();
		//allElements.push_back(nextNode);
		queueNodes.pop();

		if (!nextNode->isLeafNode) {
			for (int childInd = 0; childInd < nextNode->noChildren;
					childInd++) {
				queueNodes.push(nextNode->childrenNode.at(childInd));
			}
		} else {
			Cell newCell;
			newCell.corner[0] = nextNode->startRow * nCols + nextNode->startCol;
			int endRow = nextNode->startRow + nextNode->nodeRows - 1;
			endRow = endRow + 1;
			if (endRow > nRows - 1) {
				endRow = endRow - 1;
			}
			int endCol = nextNode->startCol + nextNode->nodeCols - 1;
			endCol = endCol + 1;
			if (endCol > nCols - 1) {
				endCol = endCol - 1;
			}
			newCell.corner[1] = endRow * nCols + nextNode->startCol;
			newCell.corner[2] = endRow * nCols + endCol;
			newCell.corner[3] = nextNode->startRow * nCols + endCol;

			for (int edgeI = 0; edgeI < 4; edgeI++) {
				if (nextNode->isHanging[edgeI] == 1) {
					int hangingNodeRow = 0;
					int hangingNodeCol = 0;
					if (edgeI == 0) // left second of center
							{
						hangingNodeRow = nextNode->startRow
								+ nextNode->nodeRows / 2;
						hangingNodeCol = nextNode->startCol;

						newCell.hang[edgeI] = hangingNodeRow * nCols
								+ hangingNodeCol;
					} else if (edgeI == 1) // bottom, down one second of center
							{
						hangingNodeRow = endRow;
						;
						hangingNodeCol = nextNode->startCol
								+ nextNode->nodeCols / 2;

						newCell.hang[edgeI] = hangingNodeRow * nCols
								+ hangingNodeCol;
					} else if (edgeI == 2) //right, right one, second of center
							{
						hangingNodeRow = nextNode->startRow
								+ nextNode->nodeRows / 2;
						hangingNodeCol = endCol;

						newCell.hang[edgeI] = hangingNodeRow * nCols
								+ hangingNodeCol;
					} else if (edgeI == 3) // top
							{
						hangingNodeRow = nextNode->startRow;
						;
						hangingNodeCol = nextNode->startCol
								+ nextNode->nodeCols / 2;

						newCell.hang[edgeI] = hangingNodeRow * nCols
								+ hangingNodeCol;
					}
				}
			}

			newCell.testVal = nextNode->val;
			newCell.testDepth = nextNode->nodeDepth;
			quadTree.at(cellCounter) = newCell;

			//cout << endl;
			/*cout << "cell write " << endl;
			 cout << "start row " << nextNode->startRow << endl;
			 cout << "start col " << nextNode->startCol << endl;
			 cout << "node rows " << nextNode->nodeRows << endl;
			 cout << "node cols " << nextNode->nodeCols << endl;
			 cout << "node val " << nextNode->val << endl;*/
			cellCounter++;
		}
	}
	*cellCount = cellCounter;
}

void ImagePreLim::TestCellIntoSubImage(vector<Cell> &quadTree,
		vector<int> &subImage, int valCellCount) {
	for (int cellInd = 0; cellInd < valCellCount; cellInd++) {
		int leftTopCorner = quadTree.at(cellInd).corner[0];
		int leftBottomCorner = quadTree.at(cellInd).corner[1];
		int rightBottomCorner = quadTree.at(cellInd).corner[2];
		int rightTopCorner = quadTree.at(cellInd).corner[3];

		int leftTopCornerRow = leftTopCorner / nCols;
		int leftTopCornerCol = leftTopCorner % nCols;

		int leftBottomCornerRow = leftBottomCorner / nCols;
		int leftBottomCornerCol = leftBottomCorner % nCols;

		int rightBottomCornerRow = rightBottomCorner / nCols;
		int rightBottomCornerCol = rightBottomCorner % nCols;

		int rightTopCornerRow = rightTopCorner / nCols;
		int rightTopCornerCol = rightTopCorner % nCols;

		//using only left top and right bottom
		if (rightBottomCornerRow == nRows - 1) {
			rightBottomCornerRow = nRows;
		}
		if (rightBottomCornerCol == nCols - 1) {
			rightBottomCornerCol = nCols;
		}

		int writeValue = 0;
		if (quadTree.at(cellInd).testVal == 0) {
			writeValue = -1 * quadTree.at(cellInd).testDepth;
		} else {
			writeValue = quadTree.at(cellInd).testDepth;
		}

		for (int rowWrite = leftTopCornerRow; rowWrite < rightBottomCornerRow;
				rowWrite++) {
			for (int colWrite = leftTopCornerCol;
					colWrite < rightBottomCornerCol; colWrite++) {
				subImage.at(rowWrite * nCols + colWrite) = writeValue;
			}
		}
	}
}

void ImagePreLim::WriteTestSubCSVImage(vector<int> &reWriteSubImage, int wSize,
		int hSize, string testSubImageFileName) {
	char finalName[200];
	string fullName;
	fullName.assign(outputFolderName);
	strcpy(finalName, (fullName.append(testSubImageFileName)).c_str());

	int totalImageSize = hSize * wSize;

	ofstream file;
	file.open(finalName);
	file << reWriteSubImage.at(0);
	int index = 1;
	while (index < totalImageSize) {
		if (index % wSize == 0) {
			file << endl << reWriteSubImage.at(index);
		} else {
			file << "," << reWriteSubImage.at(index);
		}
		index++;
	}
	file.close();
}

Node::Node(int a_startRow, int a_startCol, int a_nodeRows, int a_nodeCols) {
	startRow = a_startRow;
	startCol = a_startCol;
	nodeRows = a_nodeRows;
	nodeCols = a_nodeCols;

	isHanging[0] = 0;
	isHanging[1] = 0;
	isHanging[2] = 0;
	isHanging[3] = 0;
}

void ImagePreLim::UnderSampleImage(vector<vector<Vertex> >& image, int uSfactor,
		vector<vector<Vertex> >& uSImage) {
	uSImage.resize(nRows / uSfactor);

	int rowDivide = nRows / uSfactor;
	int colDivide = nCols / uSfactor;

	for (int rowPortion = 0; rowPortion < rowDivide; rowPortion++) {
		int actualRow = rowPortion * uSfactor;
		vector<Vertex> rowVec(colDivide);
		for (int colPortion = 0; colPortion < colDivide; colPortion++) {
			int actualCol = colPortion * uSfactor;
			rowVec.at(colPortion) = image.at(actualRow).at(actualCol);
		}
		uSImage.at(rowPortion) = rowVec;
	}
}

void ImagePreLim::ReadImage(vector<vector<Vertex> > &image) {
	//-----> x coordinate
	//|
	//|
	//v
	//y coordinate (meaning x is horizontally, y is vertically)

	//vertex.x[0] = x coordinate
	//vertex.x[1] = y coordinate

	image.resize(nRows);

	string finalImageFileName;
	finalImageFileName.assign(inputFolderName);
	finalImageFileName.append(imageFileName);

	vector<int> array(nRows * nCols);
	ReadCSVimage(finalImageFileName, array);
	Vertex newVertex;
	for (int rowI = 0; rowI < nRows; rowI++) {
		vector<Vertex> vertexRow(nCols);
		for (int colI = 0; colI < nCols; colI++) {
			int vecIndex = rowI * nCols + colI;
			newVertex.val = array.at(vecIndex);
			newVertex.x[0] = colI;
			newVertex.x[1] = rowI;

			vertexRow.at(colI) = newVertex;
		}
		image.at(rowI) = vertexRow;
	}
}

void ImagePreLim::ReadCSVimage(string fileName, vector<int> &array) {
	char finalName[200];
	strcpy(finalName, fileName.c_str());

	ifstream fileStream(finalName);
	cout << ">> Reading CSV Image File: " + string(finalName) << endl;
	;
	string numStr;
	int number = 0;
	int ind = 0;

	while (getline(fileStream, numStr, ',')) {
		//cout << numStr << endl;
		istringstream convert(numStr);
		convert >> number;
		//cout << number << endl;
		array.at(ind) = number;
		ind++;
	}
}

string ImagePreLim::getImageFileName() {
	return this->imageFileName;
}

string ImagePreLim::getInputFolderName() {
	return this->inputFolderName;
}

string ImagePreLim::getOutputFolderName() {
	return this->outputFolderName;
}
