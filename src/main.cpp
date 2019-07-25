/*
Krishnan
40089054
*/
#include <opencv2/opencv.hpp>
#include<fstream>
#include <utility>
#include <iostream> 
#include <limits.h> 
#include <string.h> 
#include <queue> 
#include <stack> 
using namespace cv;
using namespace std; 
vector<string> colour;
void updateresdiualgraph(vector<vector<pair<int,int> > > &Residual_Graph, int Source, int Sink, int *paths, int Vertex,int flowvalue)
{
	int target,middle;
	for(target=Sink;target!=Source;target=paths[target])
		{
			int value,newvalue;
			middle=paths[target];
			vector<pair<int,int> > &row = Residual_Graph.at(middle);
        		for(int j=0; j<row.size();j++)
			{
            			pair<int,int> &p = row.at(j);
           	 		if(p.first == target)
				{
				value= p.second;
				break;
				}
				else
				{
				value=0;
				}
			}
			 
			newvalue=value-flowvalue;
			for(int j=0; j<row.size();j++)
			{
            			pair<int,int> &p = row.at(j);
           	 		if(p.first == target)
				{
				row.at(j)=make_pair(target,newvalue);
				}
				
			}
			vector<pair<int,int> > &col = Residual_Graph.at(target);
			for(int j=0; j<col.size();j++)
			{
            			pair<int,int> &p = col.at(j);
           	 		if(p.first == middle)
				{
				value= p.second;
				break;
				}
				else
				{
				value=0;
				}
			}
			 
			newvalue=value+flowvalue;
			for(int j=0; j<col.size();j++)
			{
            			pair<int,int> &p = col.at(j);
           	 		if(p.first == middle)
				{
				col.at(j)=make_pair(middle,newvalue);
				}
				
			}
		}
	
	
		
}
bool serach(vector<vector<pair<int,int> > > &Residual_Graph, int Source, int Sink, int *traversed, int Vertex) 
{
int first,head, second ;
vector<pair<int,int> > Pairs;
    pair<int,int> point;
colour.assign(Vertex, "white");
queue<int> list;
list.push(Source);
colour[Source]="black";
traversed[Source] = -1;    
    while (!list.empty()) {	
        head = list.front();
        list.pop();
        Pairs = Residual_Graph.at(head);
        for (int i=0; i<Pairs.size(); i++) {
            point = Pairs.at(i);
            first= point.first;
	    second=point.second;	   
            if (colour[first]=="white" &&  second > 0) {
                traversed[first] = head;
               colour[first] = "black";
                list.push(first);
            }
        }
        if(colour[Sink]=="black")
	{
            break;  
	}
}
 if(colour[Sink]=="black")
{
return true;
//cout<<1;
}
else
{
return false;
}
}

int pixel(int row,int column, int imagecol)
{
int currentpixel=1+ row * imagecol + column;
return currentpixel;
}

void MinCutMaxFlow(vector<vector<pair<int,int> > > &Sourcegraph, int sink, Mat &output) {
   int middle, target,value;
    vector<string> color;    
    
    queue<int> list;
    int source=0;    
    int column = output.cols,xcord=0, ycord=0, a;
    int first,head,second;
    vector<pair<int,int> > Pairs;
    pair<int,int> point;
    int Vertex= sink+1; 
    color.assign(Vertex, "white");
    vector<vector<pair<int,int> > > ResidualGraph(Sourcegraph);
    int *traverse = new int[Vertex];
    while (serach(ResidualGraph, source, sink, traverse, Vertex)) {
        int flowvalue = INT_MAX;
        for (target = sink; target != source; target = traverse[target]) {
            middle = traverse[target];
            //cout<<middle;
		vector<pair<int,int> > &row = ResidualGraph.at(middle);
        		for(int j=0; j<row.size();j++)
			{
            			pair<int,int> &p = row.at(j);
           	 		if(p.first == target)
				{
				value= p.second;
				break;
				}
				else
				{
				value=0;
				}
			}
            flowvalue = min(flowvalue, value);
        }

        updateresdiualgraph(ResidualGraph,source,sink,traverse,Vertex,flowvalue);
    }
	 
    list.push(source);
   color[source]="black";   
    while (!list.empty()) 
	{
        head = list.front();
        list.pop();
        Pairs = ResidualGraph.at(head);
        for (int i=0; i<Pairs.size(); i++) 
	{
            point = Pairs.at(i);
            first= point.first;
	    second=point.second;		
            if (color[first]=="white" &&  second > 0) 
	     {                
               color[first] = "black";
                list.push(first);
             }
         }
	}
    Vec3b bgPixel;
      	 bgPixel[0] = 255;
      	 bgPixel[1] = 255;
      	 bgPixel[2] = 255;
       	 Vec3b fgPixel;
       	 fgPixel[0] = 0;
	 fgPixel[1] = 0;
         fgPixel[2] = 0;    	
    	for (a = 0; a < Vertex; ++a) 
    {
        xcord = (a) / column;
        ycord = (a) % column;	

       if(color[a] == "black")
	{
	output.at<Vec3b>(xcord, ycord) = bgPixel;
	}
	else
	{
	output.at<Vec3b>(xcord, ycord) = fgPixel;
	}	
    }
	
    delete traverse;
return;
}
void insert(vector<pair<int,int> > &currentrow,int value,int columnvalue)
{
  if(value==0)
  {
	currentrow.push_back(make_pair(columnvalue,500000));
  }
 else
 {	
	currentrow.push_back(make_pair(columnvalue,5));
  }

}
int pixeldifference(Mat &greySource,int row,int rowincrement, int column,int columnincrement)
{
	int diffpixel= (int) greySource.at<uchar>(row, column) -(int) greySource.at<uchar>(row+rowincrement, column + columnincrement );
	return diffpixel;
} 
int main(int argc, char **argv) 
{
	
	int xcord, ycord, check,Vertex ;
	int currentedge,i,j,values0;
    if (argc != 4) 
    {
        cout << "Usage: ../seg input_image initialization_file output_mask" << endl;
        return -1;
    }

    // Load the input image
    // the image should be a 3 channel image by default but we will double check that in teh seam_carving
    Mat in_image;
    Mat gray_Source;
    in_image = imread(argv[1]);

    if (!in_image.data)
    {
        cout << "Could not load input image!!!" << endl;
        return -1;
    }

    if (in_image.channels() != 3) 
    {
        cout << "Image does not have 3 channels!!! " << in_image.depth() << endl;
        return -1;
    }
ifstream f(argv[2]);
    if (!f) 
    {
        cout << "Could not load initial mask file!!!" << endl;
        return -1;
    }

    
   vector<Point> foregroundPixel;
   vector<Point> backgroundPixel;
    Point p;
    int width = in_image.cols;
    int height = in_image.rows;
    
    int n;
    f>>n;

    
     for(int i=0;i<n;++i){
        int x, y, t;
        f>>x>>y>>t;
        
        if(x<0 || x>=width || y<0 || y>=height){
            cout<<"I valid pixel mask!"<<endl;
            return -1;
        }

        p.x=x;
        p.y=y;
        if(t==1)
	{
            foregroundPixel.push_back(p);
        } 
	else 
	{
            backgroundPixel.push_back(p);
        }
    }

       //changes color image to gray image -reference-https://docs.opencv.org/3.1.0/de/d25/imgproc_color_conversions.html 
	cvtColor(in_image, gray_Source, CV_BGR2GRAY);
	Vertex=(width*height)+2;//surce and sink
	
	vector< vector<pair<int,int> > > Sourcegraph(Vertex);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			currentedge= pixel(i,j,width);
			vector<pair<int,int> > &currentrow = Sourcegraph.at(currentedge);
			if(i==0)
			{
				if(j==0)
				{

					values0=pixeldifference(gray_Source,i,0,j,1);
					insert(currentrow,values0,pixel(i,j+1,width));						
					values0=pixeldifference(gray_Source,i,1,j,0);					
					insert(currentrow,values0,pixel(i+1,j,width));				
					
				}
				else if(j==(width-1))
				{

					values0=pixeldifference(gray_Source,i,0,j,-1);;
					insert(currentrow,values0,pixel(i,j-1,width));		
					values0=pixeldifference(gray_Source,i,1,j,0);
					insert(currentrow,values0,pixel(i+1,j,width));						
				}
				else
				{
					
					values0=pixeldifference(gray_Source,i,0,j,-1);;
					insert(currentrow,values0,pixel(i,j-1,width));
					values0=pixeldifference(gray_Source,i,0,j,1);
					insert(currentrow,values0,pixel(i,j+1,width));
					values0=pixeldifference(gray_Source,i,1,j,0);
					insert(currentrow,values0,pixel(i+1,j,width));
				}
			}
			else if(i==(height-1))
			{
				if (j == 0) 
				{
					
					values0=pixeldifference(gray_Source,i,0,j,1);
					insert(currentrow,values0,pixel(i,j+1,width));
					values0=pixeldifference(gray_Source,i,-1,j,0);
					insert(currentrow,values0,pixel(i-1,j,width));
					
				}
				else if(j==(width-1))
				{
					
					values0=pixeldifference(gray_Source,i,0,j,-1);;
					insert(currentrow,values0,pixel(i,j-1,width));
					values0=pixeldifference(gray_Source,i,-1,j,0);;
					insert(currentrow,values0,pixel(i-1,j,width));					
					
					
				}
				else
				{
					
					values0=pixeldifference(gray_Source,i,0,j,-1);
					insert(currentrow,values0,pixel(i,j-1,width));
					values0=pixeldifference(gray_Source,i,0,j,1);
					insert(currentrow,values0,pixel(i,j+1,width));
					values0=pixeldifference(gray_Source,i,-1,j,0);;
					insert(currentrow,values0,pixel(i-1,j,width));
				}

			}
			else
			{
				
				if (j == 0) 
				{
					
					values0=pixeldifference(gray_Source,i,0,j,1);
					insert(currentrow,values0,pixel(i,j+1,width));
					values0=pixeldifference(gray_Source,i,-1,j,0);
					insert(currentrow,values0,pixel(i-1,j,width));
					values0=pixeldifference(gray_Source,i,1,j,0);
					insert(currentrow,values0,pixel(i+1,j,width));
				}
				else if(j==(width-1))
				{
					
					values0=pixeldifference(gray_Source,i,0,j,-1);
					insert(currentrow,values0,pixel(i,j-1,width));
					values0=pixeldifference(gray_Source,i,1,j,0);
					insert(currentrow,values0,pixel(i+1,j,width));
					values0=pixeldifference(gray_Source,i,-1,j,0);
					insert(currentrow,values0,pixel(i-1,j,width));					
				}
				else
				{										
					
					values0=pixeldifference(gray_Source,i,0,j,-1);
					insert(currentrow,values0,pixel(i,j-1,width));					
					values0=pixeldifference(gray_Source,i,0,j,1);
					insert(currentrow,values0,pixel(i,j+1,width));
					values0=pixeldifference(gray_Source,i,1,j,0);
					insert(currentrow,values0,pixel(i+1,j,width));					
					values0=pixeldifference(gray_Source,i,-1,j,0);
					insert(currentrow,values0,pixel(i-1,j,width));
				}
			}	
		}
	}
	
	int rownumber,l,Source=0,Sink=Vertex-1;
	for (l= 0; l < foregroundPixel.size() ; ++l)
	 {
 	  rownumber=foregroundPixel.at(l).y*width+foregroundPixel.at(l).x+1;
       	  vector<pair<int,int> > &current = Sourcegraph.at(0);
	  current.push_back(make_pair((rownumber),500000));
   	 }
   	 for (l = 0; l < backgroundPixel.size() ; ++l) 
	{
         rownumber=backgroundPixel.at(l).y*width+backgroundPixel.at(l).x+1;
         vector<pair<int,int> > &currentcol = Sourcegraph.at(rownumber);
	 currentcol.push_back(make_pair(Vertex-1,500000));
    	}
	Mat out_image(in_image.rows, in_image.cols, in_image.type());	
       MinCutMaxFlow(Sourcegraph,Sink,out_image);
       imwrite( argv[3], out_image);
    
    // also display them both
    
    namedWindow( "Original image", WINDOW_AUTOSIZE );
    namedWindow( "Show Marked Pixels", WINDOW_AUTOSIZE );
    imshow( "Original image", in_image );
    imshow( "Show Marked Pixels", out_image );
    waitKey(0);
return 0;
}
