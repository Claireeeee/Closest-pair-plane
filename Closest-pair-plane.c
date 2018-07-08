//
//  main.c
//  Closest-pair-plane
//
//  Created by Claire on 2018/6/2.
//  Copyright © 2018年 Claire. All rights reserved.
//就是标准的解决方法，nlogn的复杂度吧，数据不太坏中间合并的时候很快的，
//最坏复杂度就是，合并时数量是n，每个最多计算两次吧， 我只能想到这，就是2n。递归加合并时2n，是一个nlogn
//只能用于二维平面，三维要做好多改动才能推广

//快排和合并时用的最小距函数都是一遍过，感觉要上天哦，嘿嘿嘿
//好开心呀

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define NUMBER 20;           //点的数量
#define RANGE 20;             //每个坐标值范围（因为要用随机数生成的整数坐标）



typedef int (*coorarray)[2];
                                       //二维数组的声明与命名   二维数组声明的时候是要指出小数组的长度的，这样才能分配空间   想要跟灵活可以试变长数组
coorarray randomdots(int number,int range);                           //产生随机坐标数组
coorarray _quicksort_by_one_di(coorarray str,int di,int start,int end);               //按某一维排序（只能两维）
coorarray minimum_distance_in_one_di(coorarray str,int start,int end,int di);        //用于递归的距离函数
coorarray inside_d_minimum_distance(float* d,coorarray inside_d,int length,coorarray minicoora);  //合并时用到的距离函数
float dis_in_two_dots(coorarray minicoor);                           //求两个点之间的距离



int main(void) {
    int number=NUMBER;
    int range=RANGE;
    coorarray inta=randomdots(number,range);
    printf("raw form:");
    for (int i=0;i<number;i++) {
        printf("(%d,%d)  ",inta[i][0],inta[i][1]);
    }
    printf("\n");
    /*_quicksort_by_one_di(inta,0,0,9);              //quicksort的一个测试
    printf("after:");
    for (int i=0;i<number;i++) {
        printf("(%d,%d)  ",inta[i][0],inta[i][1]);
    }
    printf("\n");*/
    int (*minicoor)[2]=minimum_distance_in_one_di(inta,0,9,0);
    printf("minidiscoor:(%d,%d) (%d,%d)   ",minicoor[0][0],minicoor[0][1],minicoor[1][0],minicoor[1][1]);
    printf("distance: %f\n",dis_in_two_dots(minicoor));
    /*printf("raw d:  %f",d);
    inside_d_minimum_distance(&d,inta,8);             //inside_dis的一个测试
    printf("%f",d);
    printf("after d:  %f",d);
    printf("\n");*/
}




coorarray randomdots(int number,int range){
    coorarray result=malloc(sizeof(coorarray)*number);
    srand((unsigned int)time(0));
    for (int i=0; i<2;i++ ) {
        for (int a=0; a<number; a++) {
            result[a][i]=rand()%range;
        }
    }
    return result;
}

coorarray _quicksort_by_one_di(coorarray str,int di,int start,int end){
    if (start==end) {
    }
    else{
        int left=start;
        int right=end;
        int mark[2]={str[left][0],str[left][1]};                   //mark记忆的基准应该是数值，不是位置，位置上的数值要变的
        while (left<right){
            for (; right>left&&str[right][di]>=mark[di];right--){
            }
            str[left][di]=str[right][di];
            if (di==0) {
            str[left][1]=str[right][1];
            }
            else{
                str[left][0]=str[right][0];
            }
            for (;left<right&&str[left][di]<=mark[di];left++){
            }
            str[right][di]=str[left][di];
            if (di==0) {
            str[right][1]=str[left][1];
            }
            else{
                str[right][0]=str[left][0];
            }
        }
        str[left][0]=mark[0];
        str[left][1]=mark[1];
        if (start!=left) {
            _quicksort_by_one_di(str, di,start,left-1);
        }
        if (right!=end) {
            _quicksort_by_one_di(str, di,right+1,end);
        }
    }
    return str;
}

coorarray  minimum_distance_in_one_di(coorarray str,int start,int end,int di){
    int (*minicoora)[2]=malloc(sizeof(int)*4);
    if ((end-start+1)==2) {
        minicoora[0][0]=str[start][0];        //或许可以改进为返回两点在坐标数组中的位置
        minicoora[0][1]=str[start][1];
        minicoora[1][0]=str[end][0];
        minicoora[1][1]=str[end][1];
        return minicoora;
    }
    if((end-start+1)==3){
        float d1=sqrt((str[start][0]-str[start+1][0])*(str[start][0]-str[start+1][0])+(str[start][1]-str[start+1][1])*(str[start][1]-str[start+1][1]));
        float d2=sqrt((str[start][0]-str[end][0])*(str[start][0]-str[end][0])+(str[start][1]-str[end][1])*(str[start][1]-str[end][1]));
        float d3=sqrt((str[end][0]-str[start+1][0])*(str[end][0]-str[start+1][0])+(str[end][1]-str[start+1][1])*(str[end][1]-str[start+1][1]));
        float d;
        if (d1<=d2) {
            d=d1;
            minicoora[0][0]=str[start][0];
            minicoora[0][1]=str[start][1];
            minicoora[1][0]=str[start+1][0];
            minicoora[1][1]=str[start+1][1];
        }
        else{d=d2;
            minicoora[0][0]=str[start][0];
            minicoora[0][1]=str[start][1];
            minicoora[1][0]=str[end][0];
            minicoora[1][1]=str[end][1];
        }
        if (d<=d3){}
        else{d=d3;
            minicoora[0][0]=str[end][0];
            minicoora[0][1]=str[end][1];
            minicoora[1][0]=str[start+1][0];
            minicoora[1][1]=str[start+1][1];}
        return minicoora;
    }
    else{
        _quicksort_by_one_di(str, di, start,end);
        /*printf("after:");                                       //输出排好的坐标数组
        for (int i=0;i<10;i++) {
            printf("(%d,%d)  ",str[i][0],str[i][1]);
        }
        printf("\n");*/
        int mid=(start+end)/2;
        //printf("mid:%d\n",mid);
        coorarray ai=minimum_distance_in_one_di(str,start,mid,di);
        coorarray bi=minimum_distance_in_one_di(str,mid+1,end,di);
        float d0=dis_in_two_dots(ai);
        //printf("d0:%f\n",d0);
        float d1=dis_in_two_dots(bi);
        //printf("d1:%f\n",d1);
        float d=(d0<=d1)?d0:d1;
        minicoora=(d0<=d1)?ai:bi;
        //printf("d:%f\n",d);
        float mid_di=(float)(str[mid][di]+str[mid+1][di])/2;
        //printf("mid_di:%f\n",mid_di);
        int a=0;
        int b=0;
        for (int i=mid;(i>=0)&&(mid_di-str[i][di])<d;i--) {
            a++;
        }
        for (int i=mid+1; (i<=end)&&(str[i][di]-mid_di)<d;i++) {
            b++;
        }
        //printf("a:%d     b:%d\n",a,b);
        if (a==0||b==0) {
        }
        else{
            coorarray inside_d=malloc(sizeof(int)*(a+b)*2);
            for (int i=0;i<a;i++) {
                inside_d[i][0]=str[mid-i][0];
                inside_d[i][1]=str[mid-i][1];
            }
            for (int i=0;i<b;i++) {
                inside_d[a+i][0]=str[mid+1+i][0];
                inside_d[a+i][1]=str[mid+1+i][1];
            }
            inside_d_minimum_distance(&d, inside_d,a+b,minicoora);
        }
        return minicoora;
    }
}

coorarray inside_d_minimum_distance(float* d,coorarray inside_d,int length,coorarray minicoora){
    _quicksort_by_one_di(inside_d,1,0,length-1);
                                                           //遍历，每个在2d范围内搜索，计算dis，记录小于d的
    for (int i=0;i<length;i++) {
        if ((i-1)>=0&&(inside_d[i][1]-inside_d[i-1][1])<*d) {    //每次只需要计算临近的距离即可（隔一个的，即使距离仍在d内，也是在下一个点的时候取得最小值）
            float dis=sqrt((inside_d[i][0]-inside_d[i-1][0])*(inside_d[i][0]-inside_d[i-1][0])+(inside_d[i][1]-inside_d[i-1][1])*(inside_d[i][1]-inside_d[i-a][1]));
            if (dis<*d) {                                  //每次更新修改当前数对
                *d=dis;
                minicoora[0][0]=inside_d[i][0];
                minicoora[0][1]=inside_d[i][1];
                minicoora[1][0]=inside_d[i-1][0];
                minicoora[1][1]=inside_d[i-1][1];
            }
        }
        if (((i+1)<length)&&(inside_d[i+1][1]-inside_d[i][1])<*d) {
            float dis=sqrt((inside_d[i+1][0]-inside_d[i][0])*(inside_d[i+1][0]-inside_d[i][0])+(inside_d[i+1][1]-inside_d[i][1])*(inside_d[i+a][1]-inside_d[i][1]));
            if (dis<*d) {
                *d=dis;
                minicoora[0][0]=inside_d[i][0];
                minicoora[0][1]=inside_d[i][1];
                minicoora[1][0]=inside_d[i+1][0];
                minicoora[1][1]=inside_d[i+1][1];
            }
        }
    }
    //printf("d after inside:%f\n",*d);
    return minicoora;

}

float dis_in_two_dots(coorarray str){
    float d=sqrt((str[0][0]-str[1][0])*(str[0][0]-str[1][0])+(str[0][1]-str[1][1])*(str[0][1]-str[1][1]));
    return d;
}
















