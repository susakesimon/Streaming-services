// Complete me
// hey i didnt see that it wasnt supposted to be dont in vs code 
// prevous comment were about the file but it worked again
#include "customparser.h"
#include <iostream>
#include <sstream>

using namespace std;

const char* error_msg_1 = "Cannot read integer n";
const char* error_msg_2 = "Error in content parsing";
const char* error_msg_3 = "Error in user parsing";

// To Do - Complete this function
void CustomFormatParser::parse(std::istream& is, std::vector<Content*>& content, std::vector<User*>& users)
{
    // Erase any old contents
    content.clear();
    users.clear();

    // TO DO - Add your code below.
		std::string empty;
		int numberOfContents;
		// is >> numberOfContents;
		if(!(is >> numberOfContents)){
			cout << "sixth" << endl;
			throw ParserError(error_msg_1);
		}
		// cout << "number of contents: " << numberOfContents << endl;
		// if(is.fail()){
		// 	throw ParserError(error_msg_1);
		// }
		getline(is, empty);
		// cout << empty << endl;

		for(int i =0; i< numberOfContents; i++){
			// getline(is, line);
			try{
				int id;
				int nr;
				int ts;
				int rating;
				int numEpisodes =0;
				int content_type;
				std::string title;
				std::string line;
				if(!(is >> id >> content_type)){
					cout << "first" << endl;
					throw ParserError(error_msg_2);
				}
				// std::cout << "second" << endl;
				std::getline(is, empty);

				is.get();
				std::getline(is, title);
				// cout << title << endl;
				// std::getline(is, title);
				// unsigned int unknown = 0;
				// while(unknown < title.size() && (title[unknown] == ' ' || title[unknown] == '\n')){
				// 	unknown++;
				// }
				// if(unknown < title.size()){
				// 	title = title.substr(unknown);
				// }


				// is.ignore();
				// if(title.empty()){
				// 	throw ParserError(error_msg_2);
				// }
				// if(!getline(is, title)){
				// 	throw ParserError(error_msg_2);
				// }
				// std::getline(is, empty);
				// std::getline(is, title); 
				// if(!getline(is, title)){
				// 	throw ParserError(error_msg_2);
				// }
				// std::getline(is >> ws, empty);

				is >> nr >> ts >> rating;
				if(is.fail()){
					cout << "second" << endl;
					cout << nr << ts << rating << endl;

					throw ParserError(error_msg_2);
					// is.clear();
					// getline(is, line);
					// continue;
				}
				// cout << nr << " " << ts << " " << rating << endl;
				// Content* makeContent = NULL;
				if(content_type == 1){
					is >> numEpisodes;
					// cout << numEpisodes << endl;
					if(is.fail()){
						cout << "third" << endl;
						is.clear();
						getline(is, line);
						continue;
					}
				}
				// if (is.fail()){
				// 	throw ParserError(error_msg_2);
				// }
				getline(is, empty);
				Content* makeContent = NULL;
				if(content_type == 1){
					makeContent = new Series(id, title, nr, ts, rating, numEpisodes);
				}
				else{
					makeContent = new Movie(id, title, nr, ts, rating);
				}
				std::getline(is, empty);
				// cout << "user line: " << empty << endl;
				// is.ignore();
				// std::getline(is, line);
				std::stringstream ss(empty);
				std::string person;
				std::vector<string> multiplePeople;

				while(ss >> person){
					makeContent->addViewer(person);
				}
				std::cout << "pushing back content\n";
				content.push_back(makeContent);

			// 	// Content* makeContent = NULL;
			// 	// if(content_type == 0){
			// 	// 	makeContent = new Movie(id, title, nr, ts, rating);
			// 	// }
			// 	else if(content_type == 1){
			// 		// is >> numEpisodes;
			// 		// if(is.fail()){
			// 		// 	throw ParserError(error_msg_3);
			// 		// }
			// 		// getline(is, empty);
			// 		// makeContent = new Series(id, title, nr, ts, rating, numEpisodes);
			// 	}
			// 	for(unsigned int w=0; w<multiplePeople.size(); w++){
			// 		makeContent->addViewer(person);
			// 	}
			// 	content.push_back(makeContent);
			}
			catch (exception &e){
				cout << "fifth" << endl;
				throw ParserError(error_msg_2);
			}
		}


		std::string user;
		// std::string templine;
		int max;
		int viewedId;
		std::vector<int> historyViewed;
		while(is >> user){
			// stringstream userString(templine);
			// is.clear();
			cout << "USER: " << user << endl;
			is >> max;
			if(is.fail()){
				cout << "ERROR!\n";
				throw ParserError(error_msg_3);
			}
			cout << "MAX: " << max << "\n";
			cout << "made it past here\n";
			// if(!(userString >> user >> max)){
			// 	throw ParserError(error_msg_3);
			// }
			// while(userString >> viewedId){
			// 	historyViewed.push_back(viewedId);
			// }
			// getline(is, empty);
			
			// for(unsigned int y=0; y<historyViewed.size() ; y++){
			// 	makeUser->addToHistory(viewedId);
			// }
			// while(userString >> viewedId){
			// 	makeUser->addToHistory(viewedId);
			// }
			// users.push_back(makeUser);
			std::string viewedLine;
			std::string otherStuff;
			// getline(is >> std::ws, empty);
			// cout << "other emptu line " << empty << endl;
			getline(is, viewedLine);
			getline(is, viewedLine);
			std::cout << viewedLine << "\n";
			// getline (is, viewedLine);
			// cout << "other viewed line " << viewedLine << endl;
			stringstream userString(viewedLine);
			// userString >> otherStuff;
			User* makeUser = new User(user, max);
			while(userString >> viewedId){
				// userString >> otherStuff;
				// cout << "viewedID" << viewedId << endl;
				makeUser->addToHistory(viewedId);
				
			}
			users.push_back(makeUser);
		}

} 