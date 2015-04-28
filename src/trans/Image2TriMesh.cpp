#include "Image2TriMesh.h"
#include <algorithm>
#include <iostream>

Vertex::Vertex() {
	x[0] = 0.;
	x[1] = 0.;
	val = 0;
}

bool Vertex::operator==(const Vertex& pt) {
	return (x[0] == pt.x[0] && x[1] == pt.x[1]);
}

Vertex Vertex::operator+(const Vertex& pt) {
	Vertex tmp;
	tmp.x[0] = x[0] + pt.x[0];
	tmp.x[1] = x[1] + pt.x[1];
	return tmp;
}

Vertex Vertex::operator-(const Vertex& pt) {
	Vertex tmp;
	tmp.x[0] = x[0] - pt.x[0];
	tmp.x[1] = x[1] - pt.x[1];
	return tmp;
}

Vertex Vertex::operator/(const double& c) {
	Vertex tmp;
	tmp.x[0] = x[0] / c;
	tmp.x[1] = x[1] / c;
	return tmp;
}

Vertex Vertex::operator*(const double& c) {
	Vertex tmp;
	tmp.x[0] = x[0] * c;
	tmp.x[1] = x[1] * c;
	return tmp;
}

//////////////////////////////////////////////////////

void Image2TriMesh_2D::SetProblem(const vector<vector<Vertex> >& pts) {
	cellpts.clear();
	cells.clear();
	unsigned int i, j, count(0), nrow(pts.size()), ncol(pts[0].size());
	cellpts.resize(nrow * ncol);
	cells.resize((nrow - 1) * (ncol));
	for (i = 0; i < pts.size(); i++) {
		for (j = 0; j < pts[i].size(); j++) {
			cellpts[count].x[0] = pts[i][j].x[0];
			cellpts[count].x[1] = pts[i][j].x[1];
			cellpts[count].val = pts[i][j].val;
			//if(pts[i][j].val!=0)
			//{
			//        cout<<pts[i][j].val<<'\n';
			//        getchar();
			//}
			count++;
		}
	}
	count = 0;
	for (i = 0; i < nrow - 1; i++) {
		for (j = 0; j < ncol - 1; j++) {
			cells[count].corner[0] = i * ncol + j;
			cells[count].corner[1] = i * ncol + j + 1;
			cells[count].corner[2] = (i + 1) * ncol + j + 1;
			cells[count].corner[3] = (i + 1) * ncol + j;
			count++;
		}
	}
}

void Image2TriMesh_2D::ReadImage(string fn, vector<vector<Vertex> >& pts) {
	//input: Image data, e.g. .txt file
	//output: point coordinates, point values
}

void Image2TriMesh_2D::WriteTriMesh(string fn) {
	//input: point coordinates, connectivity of points that define triangles
	//output: .stl file
}

void Image2TriMesh_2D::QuadTreeSub() {
	//input: image data from ReadImage()
	//output: quad tree struture, each edge of a cell at most have one hanging node; see Class Cell
}

void Image2TriMesh_2D::MeshGenerator() {
	//input: quad tree struture from QuadTreeSub()
	//output: triangles
}

//void Image2TriMesh_2D::BoundaryCellSplit(const Cell& cl)
//{
//        //int caseid=FindCase(cl);
//}

void Image2TriMesh_2D::UniformMeshGenerator() {
	unsigned int i;
	for (i = 0; i < cells.size(); i++) {
		int caseid = FindCase(cells[i]);
		//cout<<caseid<<'\n';
		//if(caseid!=0)
		//{
		//        cout<<caseid<<'\n';
		//        getchar();
		//}
		if (caseid == 1)
			Case1(cells[i]);
		else if (caseid == 2)
			Case2(cells[i]);
		else if (caseid == 3)
			Case3(cells[i]);
		else if (caseid == 4)
			Case4(cells[i]);
		else if (caseid == 5)
			Case5(cells[i]);
	}
}

int Image2TriMesh_2D::FindCase(Cell& cl) {
	int caseid(0);
	int flag[4] = { cellpts[cl.corner[0]].val, cellpts[cl.corner[1]].val,
			cellpts[cl.corner[2]].val, cellpts[cl.corner[3]].val };
	int count(0);
	for (int i = 0; i < 4; i++) {
		if (flag[i] == 1)
			count++;
	}
	if (count == 4) {
		caseid = 1;
	} else if (count == 3) {
		caseid = 2;
		int* it = find(flag, flag + 4, 0);
		int start = it - flag;
		int temp[4] = { cl.corner[0], cl.corner[1], cl.corner[2], cl.corner[3] };
		for (int i = 0; i < 4; i++) {
			cl.corner[i] = temp[(start + i) % 4];
		}
	} else if (count == 2) {
		if ((flag[0] == 0 && flag[1] == 1 && flag[2] == 0 && flag[3] == 1)
				|| (flag[0] == 1 && flag[1] == 0 && flag[2] == 1 && flag[3] == 0)) {
			caseid = 4;
			int* it = find(flag, flag + 4, 0);
			int start = it - flag;
			int temp[4] = { cl.corner[0], cl.corner[1], cl.corner[2],
					cl.corner[3] };
			for (int i = 0; i < 4; i++) {
				cl.corner[i] = temp[(start + i) % 4];
			}
		} else {
			caseid = 3;
			int start(0);
			int temp[4] = { cl.corner[0], cl.corner[1], cl.corner[2],
					cl.corner[3] };
			if (flag[0] == 0 && flag[1] == 0 && flag[2] == 1 && flag[3] == 1)
				start = 0;
			else if (flag[0] == 1 && flag[1] == 0 && flag[2] == 0
					&& flag[3] == 1)
				start = 1;
			else if (flag[0] == 1 && flag[1] == 1 && flag[2] == 0
					&& flag[3] == 0)
				start = 2;
			else
				start = 3;
			for (int i = 0; i < 4; i++) {
				cl.corner[i] = temp[(start + i) % 4];
			}
		}
	} else if (count == 1) {
		caseid = 5;
		int* it = find(flag, flag + 4, 1);
		int start = it - flag;
		int temp[4] = { cl.corner[0], cl.corner[1], cl.corner[2], cl.corner[3] };
		for (int i = 0; i < 4; i++) {
			cl.corner[i] = temp[(start + i) % 4];
		}
	} else {
		caseid = 0;
	}
	return caseid;
}

void Image2TriMesh_2D::AppendVertex(const Cell& cl, int cid[4]) {
	for (int i = 0; i < 4; i++) {
		if (cellpts[cl.corner[i]].val == 1) {
			vector<Vertex>::iterator it = find(tripts.begin(), tripts.end(),
					cellpts[cl.corner[i]]);
			cid[i] = it - tripts.begin();
			if (it == tripts.end()) {
				tripts.push_back(cellpts[cl.corner[i]]);
			}
		} else {
			cid[i] = -1;
		}
	}
}

void Image2TriMesh_2D::Case1(const Cell& cl) {
	int cid[4];
	AppendVertex(cl, cid);
	Triangle tri1, tri2;
	tri1.id[0] = cid[0];
	tri1.id[1] = cid[2];
	tri1.id[2] = cid[3];
	tri2.id[0] = cid[0];
	tri2.id[1] = cid[1];
	tri2.id[2] = cid[2];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
}

void Image2TriMesh_2D::Case2(const Cell& cl) {
	int cid[4];
	AppendVertex(cl, cid);
	Vertex pt1, pt2;
	pt1 = (cellpts[cl.corner[0]] + cellpts[cl.corner[1]]) / 2.;
	pt2 = (cellpts[cl.corner[0]] + cellpts[cl.corner[3]]) / 2.;
	vector<Vertex>::iterator it1 = find(tripts.begin(), tripts.end(), pt1);
	int loc1 = it1 - tripts.begin();
	if (it1 == tripts.end()) {
		tripts.push_back(pt1);
	}
	vector<Vertex>::iterator it2 = find(tripts.begin(), tripts.end(), pt2);
	int loc2 = it2 - tripts.begin();
	if (it2 == tripts.end()) {
		tripts.push_back(pt2);
	}
	Triangle tri1, tri2, tri3;
	tri1.id[0] = loc2;
	tri1.id[1] = cid[2];
	tri1.id[2] = cid[3];
	tri2.id[0] = loc1;
	tri2.id[1] = cid[2];
	tri2.id[2] = loc2;
	tri3.id[0] = loc1;
	tri3.id[1] = cid[1];
	tri3.id[2] = cid[2];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
	trimesh.push_back(tri3);
}

void Image2TriMesh_2D::Case3(const Cell& cl) {
	int cid[4];
	AppendVertex(cl, cid);
	Vertex pt1, pt2;
	pt1 = (cellpts[cl.corner[0]] + cellpts[cl.corner[3]]) / 2.;
	pt2 = (cellpts[cl.corner[1]] + cellpts[cl.corner[2]]) / 2.;
	vector<Vertex>::iterator it1 = find(tripts.begin(), tripts.end(), pt1);
	int loc1 = it1 - tripts.begin();
	if (it1 == tripts.end()) {
		tripts.push_back(pt1);
	}
	vector<Vertex>::iterator it2 = find(tripts.begin(), tripts.end(), pt2);
	int loc2 = it2 - tripts.begin();
	if (it2 == tripts.end()) {
		tripts.push_back(pt2);
	}
	Triangle tri1, tri2;
	tri1.id[0] = loc1;
	tri1.id[1] = cid[2];
	tri1.id[2] = cid[3];
	tri2.id[0] = loc1;
	tri2.id[1] = loc2;
	tri2.id[2] = cid[2];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
}

void Image2TriMesh_2D::Case4(const Cell& cl) {
	int cid[4];
	AppendVertex(cl, cid);
	Vertex pt1, pt2, pt3, pt4;
	vector<Vertex> pt(4);
	int loc[4];
	for (int i = 0; i < 4; i++) {
		pt[i] = (cellpts[cl.corner[i]] + cellpts[cl.corner[(i + 1) % 4]]) / 2.;
		vector<Vertex>::iterator it = find(tripts.begin(), tripts.end(), pt[i]);
		loc[i] = it - tripts.begin();
		if (it == tripts.end()) {
			tripts.push_back(pt[i]);
		}
	}
	Triangle tri1, tri2;
	tri1.id[0] = loc[3];
	tri1.id[1] = loc[2];
	tri1.id[2] = cid[3];
	tri2.id[0] = loc[0];
	tri2.id[1] = cid[1];
	tri2.id[2] = loc[1];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
}

void Image2TriMesh_2D::Case5(const Cell& cl) {
	int cid[4];
	AppendVertex(cl, cid);
	Vertex pt1, pt2;
	pt1 = (cellpts[cl.corner[0]] + cellpts[cl.corner[1]]) / 2.;
	pt2 = (cellpts[cl.corner[0]] + cellpts[cl.corner[3]]) / 2.;
	vector<Vertex>::iterator it1 = find(tripts.begin(), tripts.end(), pt1);
	int loc1 = it1 - tripts.begin();
	if (it1 == tripts.end()) {
		tripts.push_back(pt1);
	}
	vector<Vertex>::iterator it2 = find(tripts.begin(), tripts.end(), pt2);
	int loc2 = it2 - tripts.begin();
	if (it2 == tripts.end()) {
		tripts.push_back(pt2);
	}
	Triangle tri1;
	tri1.id[0] = cid[0];
	tri1.id[1] = loc1;
	tri1.id[2] = loc2;
	trimesh.push_back(tri1);
}

void Image2TriMesh_2D::Case1_adap(Cell& cl) {
	int caseid = FindCaseAdap(cl);
	if (caseid == 1)
		Case1_1(cl);
	else if (caseid == 2)
		Case1_2(cl);
	else if (caseid == 3)
		Case1_3(cl);
	else if (caseid == 4)
		Case1_4(cl);
	else if (caseid == 5)
		Case1_5(cl);
}

int Image2TriMesh_2D::FindCaseAdap(Cell& cl) {
	int caseid(0);
	int count(0);
	for (int i = 0; i < 4; i++) {
		if (cl.hang[i] != -1)
			count++;
	}
	if (count == 1) {
		caseid = 1;
		int start(0);
		for (int i = 0; i < 4; i++) {
			if (cl.hang[i] != -1) {
				start = i;
				break;
			}
		}
		int temp1[4] =
				{ cl.corner[0], cl.corner[1], cl.corner[2], cl.corner[3] };
		int temp2[4] = { cl.hang[0], cl.hang[1], cl.hang[2], cl.hang[3] };
		for (int i = 0; i < 4; i++) {
			cl.corner[i] = temp1[(i + start) % 4];
			cl.hang[i] = temp2[(i + start) % 4];
		}
	} else if (count == 2) {
		if ((cl.hang[0] != -1 && cl.hang[2] != -1)
				|| (cl.hang[1] != -1 && cl.hang[3] != -1)) {
			caseid = 3;
		} else {
			caseid = 2;
		}
		int start(0);
		for (int i = 0; i < 4; i++) {
			if (cl.hang[i] != -1) {
				start = i;
				break;
			}
		}
		int temp1[4] =
				{ cl.corner[0], cl.corner[1], cl.corner[2], cl.corner[3] };
		int temp2[4] = { cl.hang[0], cl.hang[1], cl.hang[2], cl.hang[3] };
		for (int i = 0; i < 4; i++) {
			cl.corner[i] = temp1[(i + start) % 4];
			cl.hang[i] = temp2[(i + start) % 4];
		}
	} else if (count == 3) {
		caseid = 4;
		int start(0);
		for (int i = 0; i < 4; i++) {
			if (cl.hang[i] != -1) {
				start = i;
				break;
			}
		}
		int temp1[4] =
				{ cl.corner[0], cl.corner[1], cl.corner[2], cl.corner[3] };
		int temp2[4] = { cl.hang[0], cl.hang[1], cl.hang[2], cl.hang[3] };
		for (int i = 0; i < 4; i++) {
			cl.corner[i] = temp1[(i + start) % 4];
			cl.hang[i] = temp2[(i + start) % 4];
		}
	} else if (count == 4) {
		caseid = 5;
	} else {
		caseid = 0;
	}
	return caseid;
}

void Image2TriMesh_2D::AppendHandingNode(const Cell& cl, int hid[4]) {
	for (int i = 0; i < 4; i++) {
		if (cl.hang[i] != -1) {
			vector<Vertex>::iterator it = find(tripts.begin(), tripts.end(),
					cellpts[cl.hang[i]]);
			hid[i] = it - tripts.begin();
			if (it == tripts.end()) {
				tripts.push_back(cellpts[cl.hang[i]]);
			}
		} else {
			hid[i] = -1;
		}
	}
}

void Image2TriMesh_2D::Case1_1(const Cell& cl) {
	int cid[4], hid[4];
	AppendVertex(cl, cid);
	AppendHandingNode(cl, hid);
	Triangle tri1, tri2, tri3;
	tri1.id[0] = cid[0];
	tri1.id[1] = hid[0];
	tri1.id[2] = cid[3];
	tri2.id[0] = hid[0];
	tri2.id[1] = cid[2];
	tri2.id[2] = cid[3];
	tri3.id[0] = hid[0];
	tri3.id[1] = cid[1];
	tri3.id[2] = cid[2];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
	trimesh.push_back(tri3);
}

void Image2TriMesh_2D::Case1_2(const Cell& cl) {
	int cid[4], hid[4];
	AppendVertex(cl, cid);
	AppendHandingNode(cl, hid);
	Triangle tri1, tri2, tri3, tri4;
	tri1.id[0] = cid[0];
	tri1.id[1] = hid[0];
	tri1.id[2] = cid[3];
	tri2.id[0] = hid[0];
	tri2.id[1] = hid[1];
	tri2.id[2] = cid[3];
	tri3.id[0] = hid[0];
	tri3.id[1] = cid[1];
	tri3.id[2] = hid[1];
	tri4.id[0] = hid[1];
	tri4.id[1] = cid[2];
	tri4.id[2] = cid[3];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
	trimesh.push_back(tri3);
	trimesh.push_back(tri4);
}

void Image2TriMesh_2D::Case1_3(const Cell& cl) {
	int cid[4], hid[4];
	AppendVertex(cl, cid);
	AppendHandingNode(cl, hid);
	Triangle tri1, tri2, tri3, tri4;
	tri1.id[0] = cid[0];
	tri1.id[1] = hid[1];
	tri1.id[2] = cid[3];
	tri2.id[0] = cid[0];
	tri2.id[1] = hid[0];
	tri2.id[2] = hid[1];
	tri3.id[0] = hid[0];
	tri3.id[1] = cid[2];
	tri3.id[2] = hid[1];
	tri4.id[0] = hid[1];
	tri4.id[1] = cid[1];
	tri4.id[2] = cid[2];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
	trimesh.push_back(tri3);
	trimesh.push_back(tri4);
}

void Image2TriMesh_2D::Case1_4(const Cell& cl) {
	int cid[4], hid[4];
	AppendVertex(cl, cid);
	AppendHandingNode(cl, hid);
	Triangle tri1, tri2, tri3, tri4, tri5;
	tri1.id[0] = cid[0];
	tri1.id[1] = hid[2];
	tri1.id[2] = cid[3];
	tri2.id[0] = cid[0];
	tri2.id[1] = hid[0];
	tri2.id[2] = hid[2];
	tri3.id[0] = hid[0];
	tri3.id[1] = hid[1];
	tri3.id[2] = hid[2];
	tri4.id[0] = hid[0];
	tri4.id[1] = cid[1];
	tri4.id[2] = hid[1];
	tri5.id[0] = hid[1];
	tri5.id[1] = cid[2];
	tri5.id[2] = hid[2];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
	trimesh.push_back(tri3);
	trimesh.push_back(tri4);
	trimesh.push_back(tri5);
}

void Image2TriMesh_2D::Case1_5(const Cell& cl) {
	int cid[4], hid[4];
	AppendVertex(cl, cid);
	AppendHandingNode(cl, hid);
	Triangle tri1, tri2, tri3, tri4, tri5, tri6;
	tri1.id[0] = cid[0];
	tri1.id[1] = hid[0];
	tri1.id[2] = hid[3];
	tri2.id[0] = hid[0];
	tri2.id[1] = hid[2];
	tri2.id[2] = hid[3];
	tri3.id[0] = hid[3];
	tri3.id[1] = hid[2];
	tri3.id[2] = cid[3];
	tri4.id[0] = hid[0];
	tri4.id[1] = hid[1];
	tri4.id[2] = hid[2];
	tri5.id[0] = hid[0];
	tri5.id[1] = cid[1];
	tri5.id[2] = hid[1];
	tri5.id[0] = hid[1];
	tri5.id[1] = cid[2];
	tri5.id[2] = hid[2];
	trimesh.push_back(tri1);
	trimesh.push_back(tri2);
	trimesh.push_back(tri3);
	trimesh.push_back(tri4);
	trimesh.push_back(tri5);
}
