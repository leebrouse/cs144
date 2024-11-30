# Lab1: Stitching substrings into a byte stream
At First ,let we see the member variable in my "reassembler.hh"
 ## reassembler.hh
 ```
#pragma once

#include "byte_stream.hh"
#include <set>
#include <string>
#include <vector>

// unassemble package struct
struct Interval
{
  uint64_t first_index;
  uint64_t end_index;
  std::string data;

  // 重载小于操作符
  bool operator<( const Interval& other ) const
  {
    // 优先按 first_index 比较
    if ( first_index != other.first_index ) {
      return first_index < other.first_index;
    }

    // 如果 first_index 相同，按 end_index 比较
    if ( end_index != other.end_index ) {
      return end_index < other.end_index;
    }

    return data < other.data;
  }
};

class Reassembler
{
public:
  // Construct Reassembler to write into given ByteStream.
  explicit Reassembler( ByteStream&& output ) : output_( std::move( output ) ) {}

  void insert( uint64_t first_index, std::string data, bool is_last_substring );

  // How many bytes are stored in the Reassembler itself?
  uint64_t bytes_pending() const;

  // Access output stream reader
  Reader& reader() { return output_.reader(); }
  const Reader& reader() const { return output_.reader(); }

  // Access output stream writer, but const-only (can't write from outside)
  const Writer& writer() const { return output_.writer(); }

private:
  ByteStream output_;             // the Reassembler writes to this ByteStream
  std::set<Interval> reBuffer {}; // Reasssembler buffer including Interval structers
  uint64_t nxt_index {};// The next index number that byte stream want to get.
  uint64_t eof_idx = UINT64_MAX; //eof tag
};
 ```
 # Target:
 - What is a reassembler?
 - How to solve the overlapping problem in reassembler?
 - How to stitch substrings for make a new string?
 ## Q1: What is a reassembler?
 ### The below image is reassembler in the lab file.
![reassembler_image](/cs144%20Note/image/lab1/reassembler_image.png)
## Extra Question: What is the function of the reassembler?
The obligation of TCP is to provide a relible byte stream,So the function of the reassembler is to keep data is not duplicated and disorder.
## Example:
### 1. Orderliness :
![Disorder_image](/cs144%20Note/image/lab1/disorder_image.png)
### 2.No Duplicated :
![Repeated_image](/cs144%20Note/image/lab1/repeated_image.png)

 ## Q2: How to solve the overlapping problem in reassembler? 
 ## Example:
  ![overlapping](/cs144%20Note/image/lab1/overlapping.png)
  - Detect the package1 end_index and package2 first_index
  - Detect the package1 end_index and package2 end_index
  - Save the red part in the package1 and stitch with the package2 data to make a new string (Tip: use substr() in the string)
 ## Q3: How to stitch substrings for make a new string?
  ```
  // IF the condition is true
   if ( it->first_index <= last.end_index ) {
      if ( last.end_index <= it->end_index ) {
        //package1.end_index=package2.end_index
        //package1.data=package1.data.substr(0,package2.first_index - package1.first_index)+package2.data
      }
    } 
  ``` 
  - Change the end_index in the package1 using the package2 end_index
  - Stitching the package1 red part with the package2 data,then assign the value to the package1.
  - Tip: "package1.data.substr(0,package2.first_index - package1.first_index)" is red part in the package1 
 # Pseudocode is Here:
 ```
 #include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Detects whether the byte stream is closed

  //if is_last_substring is true,assign the eof_idx value.
 
  // Adjust window boundaries

  // Handle the overlapping intervals
  
  //clear reBuffer and reassgin the value for the reBuffer

  // Push the intervals into the byte stream

  //If the nxt_index is eof(is_last_substring),close the byte stream.
}

uint64_t Reassembler::bytes_pending() const
{
  //1.create pendcnt varible.
  //2.if reBuffer is empty return strightly
  //3.Iterate over the values in the rebuffer
  //4.return pendcnt
}
 ```