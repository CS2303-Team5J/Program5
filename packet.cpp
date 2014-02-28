namespace EIN_JRW_Lab5
{
  simNode packet::getNextDest()
  {
    simnode* simPtr;
    path.pop(simPtr);
    return simPtr;
  }
  void Packet::setPath(std::string imputpath)
  {
    char delim = ' ';
        int start = 0;
        int end;
	int i;
        vector<string> splitString;
        // Until find returns nothing (string::npos)
        while((end = imputpath.find(delim,start)) != string::npos)
	  {
	    // Get the substring up to the delimter
	    // end is the position of the delimiting string
	    splitString.push_back(inputpath.substr(start,end-start));
	    start = end + delim.length();
	  }
        // Get the last remaining word
        splitString.push_back(path.substr(start));
        splitString
      }
  for(i = 0; i < global:size; i++)
    {
      path.push(router.findRouter(splitString[i]));
    }
  }
