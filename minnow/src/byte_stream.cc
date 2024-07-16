#include "byte_stream.hh"
 
using namespace std;


ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  // Your code here.
  return is_close_;
}

void Writer::push( string data )
{
  // Your code here.
  if (is_close_)
  {
    return;
  }
  
  uint64_t push_size=min(data.length(),available_capacity());

  buffer.append(data.substr(0,push_size));
  push_cnt+=push_size;
  return;
}

void Writer::close()
{
  // Your code here.
  is_close_=true;
}

uint64_t Writer::available_capacity() const
{
  // Your code here.
  return capacity_-buffer.size();
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return push_cnt;
}

bool Reader::is_finished() const
{
  // Your code here.
  return (is_close_&&pop_cnt==push_cnt);
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return pop_cnt;
}

string_view Reader::peek() const
{
  // Your code here.
  if(!buffer.size()){
    return {};
  }

  return string_view(buffer);
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  uint64_t pop_size=min(len,buffer.size());

  buffer=buffer.substr(pop_size);
  pop_cnt+=pop_size;
}

uint64_t Reader::bytes_buffered() const
{
  // Your code here.
  return buffer.size();
}
