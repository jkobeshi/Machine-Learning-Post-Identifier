// Project UID db1f506d06d84ab787baf250c265e24e
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <cmath>
#include "csvstream.h"
using namespace std;


set<string> unique_words(const string& str) {
	istringstream source(str);
	set<string> words;
	string word;
	while (source >> word) {
		words.insert(word);
	}
	return words;
}

class classifier {
public:
	void LearnRow(pair<string, string> it, int index) {
		//storing data
		trainingData[index].first = (it.first);
		trainingData[index].second = (it.second);
		//storing number of posts for each label
		label_countPost[it.first] += 1.0;
		//storing number of posts for each word + posts for each word and label
		set<string> uniques = unique_words(it.second);
		for (set<string>::iterator itr = uniques.begin(); itr != uniques.end(); itr++) {
			word_countPost[*itr] += 1.0;
			labWor_countPost[{it.first, *itr}] += 1.0;
		}
	}
	double log_prior(string label) {
		return log(label_countPost[label] / double(trainingData.size()));
	}
	double log_likelihood(string label, string word) {
		double numTpost = double(trainingData.size());
		if (word_countPost[word] == 0) {
			return log(1.0 / numTpost);
		}
		else if (labWor_countPost[{label, word}] == 0) {
			return log(word_countPost[word] / numTpost);
		}
		else {
			return log(labWor_countPost[{label, word}] / label_countPost[label]);
		}
	}
	pair<string, double> log_probability_score(string cont) {//not finished
		set<string> X = unique_words(cont);
		int index = 0; pair<string, double> maxPair;
		for (auto i : label_countPost) {
			auto label = i.first;
			double probability = log_prior(label);
			for (set<string>::iterator itr = X.begin(); itr != X.end(); itr++) {
				probability += log_likelihood(label, *itr);
			}
			if (index == 0) { maxPair = { label, probability }; index++; }
			else {
				if (maxPair.second < probability) {
					maxPair = { label, probability };
				}
			}
		}
		return maxPair;
	}
	void testData(string filename, map<string, string> row) {
		csvstream Data(filename);
		cout << "test data:\n";
		int total_cnt = 0, cor_cnt = 0;
		while (Data >> row) {
			pair<string, double> prediction = log_probability_score(row["content"]);
			cout << "  correct = " << row["tag"] << ", predicted = " << prediction.first 
				<< ", log-probability score = " << prediction.second
				<< "\n  content = " << row["content"] << endl << endl;
			if (row["tag"] == prediction.first) { cor_cnt++; }
			total_cnt++;
		}
		cout << "performance: " << cor_cnt << " / " 
			<< total_cnt << " posts predicted correctly\n";
	}
	void Print() {
		cout << "trained on " << int(trainingData.size()) << " examples\n\n";
	}
	void Print_Debug() {
		cout << "training data:\n";
		for (int i = 0; i < int(trainingData.size()); i++) {
			cout << "  label = " << trainingData[i].first 
				<< ", content = " << trainingData[i].second << endl;
		}
		cout << "trained on " << trainingData.size() << " examples\n"
			<< "vocabulary size = " << int(word_countPost.size()) << endl << endl
			<< "classes:\n";
		for (auto i : label_countPost) {
			cout << "  " << i.first << ", " << i.second 
				<< " examples, log-prior = " << log_prior(i.first) << "\n";
		}
		cout << "classifier parameters:\n";
		for (auto i : labWor_countPost) {
			auto labWor = i.first;
			cout << "  " << labWor.first << ":" 
				<< labWor.second << ", " << "count = " << i.second 
				<< ", log-likelihood = " << log_likelihood(labWor.first, labWor.second) << "\n";
		}
		cout << endl;
	}
private:
	map<string, double> word_countPost;
	map<string, double> label_countPost;
	map<pair<string, string>, double> labWor_countPost;
	map<int, pair<string, string>> trainingData;
};
int main(int argc, char* argv[]) {
	cout.precision(3);
	if (argc > 4 || argc < 3 || (argc == 4 && string(argv[3]) != "--debug")) {
		cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
		return 1;
	}
	ifstream fin1(argv[1]);
	ifstream fin2(argv[2]);
	if (!fin1.is_open()) {
		cout << "Error opening file: " << argv[1] << endl;
		return 1;
	}
	if (!fin2.is_open()) {
		cout << "Error opening file: " << argv[2] << endl;
		return 1;
	}
	csvstream csvin1(fin1);
	classifier Machine;
	map<string, string> row; int index = 0;
	while (csvin1 >> row) {
		Machine.LearnRow({ row["tag"], row["content"] }, index);
		index++;
	}
	
	if (argc == 4 && string(argv[3]) == "--debug") { Machine.Print_Debug(); }
	else { Machine.Print(); }
	Machine.testData(argv[2], row);
}