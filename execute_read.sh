#!/usr/bin/bash

training_images=./training_images
training_labels=./training_labels
test_images=./testing_images
test_labels=./testing_labels

function execute {
	./data_picker.exe $1 $2;
}
function error {
	echo "ERROR: Usage: ./executable [test/training] [images/label]";
	echo "Try using the --help option for more help.";
}

if [[ "$1" == "--help" ]]; then
	echo "Usage: ./executable [options] [type]"
	echo "";
	echo "Options:";
	echo "	test:";
	echo "		The test option chooses from either of the files designated for the testing";
	echo "		portion of the image files.";
	echo "	training:";
	echo "		The training option chooses from either of the files designated for the";
	echo "		training portion of the image files.";
	echo "";
	echo "Type:";
	echo "	images:";
	echo "		Takes from the image file.";
	echo "	labels:";
	echo "		Takes from the label file.";
	exit 0;
fi

if [[ "$1" == "test" ]]; then
	if [[ "$2" == "images" ]]; then
		execute testing_images images;
	elif [[ "$2" == "labels" ]]; then
		execute testing_labels labels;
	else
		error; exit 1;
	fi
elif [[ "$1" == "training" ]]; then
	if [[ "$2" == "images" ]]; then
		execute training_images images;
	elif [[ "$2" == "labels" ]]; then
		execute training_labels labels;
	else
		error; exit 1;
	fi
else
	error; exit 1;
fi
