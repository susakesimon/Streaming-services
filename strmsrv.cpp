#include "strmsrv.h"
#include <iostream>
#include <fstream>
using namespace std;

// To do - Complete this function
StreamService::StreamService()
: cUser_ (NULL)
{
    // Update as needed


}

// To do - Complete this function
StreamService::~StreamService()
{
	for(unsigned int i=0; i < content_.size(); i++){
		delete content_[i];
		// content_.pop_back();
	}

	for(unsigned int i=0; i < users_.size(); i++){
		delete users_[i];
		// users_.pop_back();
	}

}

// Complete - Do not alter
void StreamService::readAndParseData(std::istream& is, Parser& p)
{
    p.parse(is, content_, users_);
    cout << "Read " << content_.size() << " content items." << endl;
    cout << "Read " << users_.size() << " users." << endl;
}

// To do - Complete this function
void StreamService::userLogin(const std::string& uname)
{
	if(cUser_ != NULL){
		// check if there is more to do for this
		// aleady logedin
		throw runtime_error("already logedin"); 
	}
	// location inside the vector
	int loc = getUserIndexByName(uname);
	if(loc == -1){
		// user doesnt exist
		throw invalid_argument("user doesnt exist");
	}
	cUser_ = users_[loc];

}

// To do - Complete this function
void StreamService::userLogout()
{
	cUser_ = NULL;
}

// To do - Complete this function
std::vector<CID_T> StreamService::searchContent(const std::string& partial) const
{
    std::vector<CID_T> results;
    for(size_t i = 0; i < content_.size(); i++){
        // TO DO - modify this to also push back when the string 'partial'
        //  is contained in the name of the current content. Lookup the string
        //  class documentation to find an appropriate function that can be used
        //  to do this simply.

				// use the find and the string::npos
        if(partial == "*" || content_[i]->name().find(partial) != std::string::npos){
            results.push_back(i);
        }        
    }
    return results;
}

// Complete - Do not alter
std::vector<CID_T> StreamService::getUserHistory() const
{
    throwIfNoCurrentUser();
    return cUser_->history;
}

// To do - Complete this function
void StreamService::watch(CID_T contentID)
{
	throwIfNoCurrentUser();
	// finifh this function 
	bool valid = isValidContentID(contentID);
	if(!valid){
		// print something
		throw range_error("contentID is not valid");
	}
	// throwIfNoCurrentUser();
	// in user.cpp
	bool watched = cUser_->haveWatched(contentID);
	if(watched){
		return;
	}
	// rating() is inside content.h
	Content* temp = content_[contentID];
	if( temp->rating() > cUser_->ratingLimit){
		throw RatingLimitError("content's rating is above the User's rating limit");
	}

	// finifh this
	// in user.cpp and in content.h
	content_[contentID]-> addViewer(cUser_->uname); 
	cUser_-> addToHistory(contentID); 
}

// To do - Complete this function
void StreamService::reviewShow(CID_T contentID, int numStars)
{
	throwIfNoCurrentUser();
	if(!isValidContentID(contentID)){
		// print something
		throw ReviewRangeError("contentID is not valid");		
	}
	if( numStars > 5 || numStars < 0) {
		// invalid
		throw ReviewRangeError("the number of stars is out of the range 0-5");
	}
	
	content_[contentID]->review(numStars);
}

// To do - Complete this function
CID_T StreamService::suggestBestSimilarContent(CID_T contentID) const
{
    // Change this when you are ready, but for now it is a 
    // dummy implementation
    // return -1;
		vector<int> viewHistory;
		vector<int> unique;
		
		for(unsigned int i=0; i<users_.size(); i++){
			if(users_[i]->haveWatched(contentID)){
				// viewHistory.push_back(i);
				for(unsigned int j=0; j< users_[i]->history.size(); j++){
					bool notfoundunique = false;
					if(cUser_->haveWatched(users_[i]->history[j]) || users_[i]->history[j] == contentID){
						continue;
					}
					for(unsigned int w=0; w<unique.size(); w++){
						if(unique[w] == users_[i]->history[j]){
							
							// int temp = unique.find(users_[i]->history(j));
							viewHistory[w]++;

							notfoundunique = true;
							break;
						}
					} 
					if(notfoundunique == false){
						unique.push_back(users_[i]->history[j]);
						viewHistory.push_back(1);
					}
				}
			}

		}
		if(unique.size() == 0){
			return -1;
		}
		int tempMax =0; 
		int tempLoc = 0;
		for(unsigned int i=0; i<unique.size(); i++){
			if(viewHistory[i] > tempMax){
				tempMax = viewHistory[i];
				tempLoc=i;
			}
		}
		return unique[tempLoc];
}

// To do - Complete this function
void StreamService::displayContentInfo(CID_T contentID) const
{
    // Do not alter this
    if(! isValidContentID(contentID)){
        throw std::invalid_argument("Watch: invalid contentID");
    }

    // Call the display abitlity of the appropriate content object



}

// Complete - Do not alter
bool StreamService::isValidContentID(CID_T contentID) const
{
    return (contentID >= 0) && (contentID < (int) content_.size());
}

// Complete - Do not alter
void StreamService::throwIfNoCurrentUser() const
{
    if(cUser_ == NULL){
        throw UserNotLoggedInError("No user is logged in");
    }
}

// Complete - Do not alter
int StreamService::getUserIndexByName(const std::string& uname) const
{
    for(size_t i = 0; i < users_.size(); i++){
        if(uname == users_[i]->uname) {
            return (int)i;
        }
    }
    return -1;
}
