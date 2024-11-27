#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Your code here.
  /* Three kinds of insert problems
  1.Overlapping
  2.
  3.
  */

  // Detects whether the byte stream is closed?
  if ( output_.writer().is_closed() ) {
    return;
  }

  // 1.If Reasssembler buffer is empty,push it(Intervals) into reBuffer
  // 2.check the available_capacity in byte_stream
  uint64_t available_capacity = output_.writer().available_capacity();
  if ( reBuffer.empty() && first_index==0 ) {
    string subdata = data.substr( 0, min( data.length(), available_capacity ) );
    reBuffer.insert( { first_index, subdata, is_last_substring } );
    output_.writer().push( subdata );
    return;
  }

  //The process of reassemble
  for (const auto& interval:reBuffer)
  {
    if (interval.data==data)
    {
      break;
    }
    
  }
  

  /* If insert interval has is_last_substring tag.
    1.Reasssembler buffer clear.
    2.Close the btye_stream.
  */

  if ( is_last_substring ) {
    output_.writer().close();
    output_.reader().pop(reBuffer.size()-1);
    reBuffer.clear();
    return;
  }
}

uint64_t Reassembler::bytes_pending() const
{
  if ( reBuffer.empty() ) {
    return {};
  }

  return output_.writer().available_capacity();
}