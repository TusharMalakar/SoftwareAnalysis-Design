/*
 *  FileName: SequenceMap.h
 *  Created on: Sep 27, 2018
 *  Author: Tushar Malakar
 */
 #ifndef SequenceMap_h
#define SequenceMap_h

#include <iostream>
#include <string>
#include <vector>

class SequenceMap
{
public:
                // The Big Five:
                ~SequenceMap() = default;
                SequenceMap(const SequenceMap & rhs) = default;
                SequenceMap(SequenceMap && rhs) = default;
                SequenceMap& operator= (const SequenceMap & rhs) = default;
                SequenceMap& operator= (SequenceMap && rhs) = default;
                //end of big five


                /**
                A constructor SequenceMap(const string &a_rec_seq, const
                string &an_enz_acro),that constructs a SequenceMap from two strings
                (note that now the vector enzyme_acronyms_ will contain just one element,
                the an_enz_acro).
                **/
                SequenceMap(const std::string &a_rec_seq_, const std::string &enz_acro_) :
                recognition_sequence_(a_rec_seq_), enzyme_acronym_{enz_acro_} {}


                /**
                bool operator<(const SequenceMap &rhs) const, that operates
                based on the regular string comparison between the
                recognition_sequence_ strings (this will be a one line function).
                **/
                bool operator<(const SequenceMap &rhs) const
                {return recognition_sequence_ < rhs.recognition_sequence_;}


                /**Overload the operator<< for SequenceMap**/
                friend std::ostream& operator<<(std::ostream& os, const SequenceMap& s_map)
                {
                os << s_map.recognition_sequence_ << " ";
                for (unsigned int i = 0; i < s_map.enzyme_acronym_.size() ; i++)
                os << s_map.enzyme_acronym_[i] << " ";
                os << std::endl;
                return os;
                }

                /**
                void Merge(const SequenceMap &other_sequence). This function
                assumes that the object’s recognition_sequence_ and
                other_sequence.recognition_sequence_ are equal to each other. The
                function Merge() merges the other_sequence.enzyme_acronym_ with
                the object’s enzyme_acronym_. The other_sequence object will not be
                affected.**/
                void Merge(const SequenceMap &other_sequence)
                {
                for (unsigned int i = 0; i < other_sequence.enzyme_acronym_.size(); i++)
                enzyme_acronym_.push_back(other_sequence.enzyme_acronym_[i]); //add the values in the argument's enzyme_acronym_ to the vector of the calling object's enzyme_acronym_
                }


                //Getter
                std::string getRecSequence() const
                {
                return recognition_sequence_;
                }


                //Prints enzyme_acronym_ in order with each element seperated by space. Ends with a new line.

                void Print_Vector() {
                for (unsigned int i = 0; i < enzyme_acronym_.size(); i++)
                std::cout << enzyme_acronym_[i] << " ";
                std::cout << std::endl;
                }

private:
                std::string recognition_sequence_;
                std::vector<std::string> enzyme_acronym_;
};

#endif
