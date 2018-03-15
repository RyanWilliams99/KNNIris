//  TrainAndTest.c
//  MLCoursework
//
// This is a fairly inefficient implentation that does not use any dynamic memory allocation
// because that wouldnot be safe on the DEWIS marking system
//
// Created by Jim Smith on 06/02/2017.
// Copyright © 2017 Jim SmithJim Smith. All rights reserved.

#include "TrainAndTest.h"
#include <math.h>
//declare this array as static but make it available to any function in this file
//in case we want to store the training examples  and use them later
static    double myModel[NUM_TRAINING_SAMPLES][ NUM_FEATURES];
//even if each item in the training set is from a diffferent class we know how many there are
static char myModelLabels[NUM_TRAINING_SAMPLES];

static int trainingSetSize=0;


int  train( double **trainingSamples, char *trainingLabels, int numSamples, int numFeatures)
{
    int returnval = 1;
    int sample, feature;
    
    //clean the model because C leaves whatever is in the memory
    for (sample=0; sample < NUM_TRAINING_SAMPLES; sample++) 
	{
        for (feature=0; feature<NUM_FEATURES; feature++) 
		{
            myModel[sample][feature] = 0.0;
        }
    }
    
    //sanity checking
    if ( numFeatures > NUM_FEATURES || numSamples > NUM_TRAINING_SAMPLES) 
	{
        fprintf(stdout,"error: called train with data set larger than spaced allocated to store it");
        returnval=0;
    }
    
    //this is a silly trivial train()_ function
    fprintf(stdout,"no ML algorithm implemented yet\n");
    
    //make a simple copy of the data we are being passed but don't do anything with it
    //I'm just giving you this for the sake of people less familiar with pointers etc.
     
     if(returnval==1) 
	 {
		//store the labels and the feature values
        trainingSetSize = numSamples;
        int index,feature;
        for (index=0; index < numSamples; index++) 
		{
			myModelLabels[index] = trainingLabels[index];
            for (feature=0; feature < numFeatures; feature++) 
			{
                myModel[index][feature] = trainingSamples[index][feature];
            }
        }
        fprintf(stdout,"data stored locally \n");
     }
    return returnval;
}

char  predictLabel(double *sample, int numFeatures)
{
	//loop trough mymodel and see which flowers types are closeses
	char prediction;
	int i = 0;
	int n = 0;
	double diffx, diffy, diffz, difft = 0;
	double dist = 0;
	double finaldist = 0;
	double currentShortest = 1000;
	int closestNeighborIndex = 0;
	double compare[NUM_FEATURES];



	for (i = 0; i < NUM_TRAINING_SAMPLES; i++) //going through row by row of training set
	{
		printf("start i loop\n ");
		for (n = 0; n < NUM_FEATURES;) //going thorugh column by column and puttting in a new array 
		{
			diffx = myModel[i][n] - sample[n];
			n++;
			diffy = myModel[i][n] - sample[n];
			n++;
			diffz = myModel[i][n] - sample[n];
			n++;
			difft = myModel[i][n] - sample[n];
			n++;
		}

		diffx = diffx * diffx;
		diffy = diffy * diffy;
		diffz = diffz * diffz;
		difft = difft * difft;

		dist = diffx + diffy + diffz + difft;

		finaldist = sqrt(dist);
		printf("FINALDIST %lf ", finaldist);
		
		if (finaldist < currentShortest)
		{
			
			currentShortest = finaldist;
			closestNeighborIndex = i;
			printf("closest neighbor updated");

		}
	}

	prediction = myModelLabels[closestNeighborIndex];
	printf("___________________________________________________________________________________________________________________________________________________________________________________________________________________________________________");
	return prediction;
}
