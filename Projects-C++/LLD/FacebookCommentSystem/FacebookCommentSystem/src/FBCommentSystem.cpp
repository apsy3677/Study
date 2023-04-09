#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Comment
{
public:
   string id;
   string msg;
   string userId;
   string postId;
   string parentId;

   // vector<Comment> comments;
   list<Comment> comments;
   // unordered_map<string, Comment*> commentIdMap;
   unordered_map<string, list<Comment>::iterator > commentIdMap;

   string getUniqueId()
   {
      static int commentId = 0;
      return "c" + to_string( commentId++ );
   }

   void setNestedDescription(const string& commentId, const string& msg)
   {
      if( commentIdMap.find( commentId ) == commentIdMap.end() )
      {
         cout << " No Nested Comment with ID " << commentId << "\n";
         return;
      }
      auto& it = commentIdMap[ commentId ];
      it->msg = msg;
   }

   Comment(string msg)
   {
      id = getUniqueId();
      this->msg = msg;
   }

   void nestedDelete(string commentId)
   {
      // Find Comm first
      if(commentIdMap.find(commentId) == commentIdMap.end() )
      {
         cout << " No Nested Comment with ID "<<commentId<<"\n";
         return;
      }
      auto &it = commentIdMap[commentId];
      comments.erase( it );
      commentIdMap.erase( commentId );
   }

   void addComment(Comment &comment)
   {
      comments.push_front( comment );
      commentIdMap[ comment.id ] = comments.begin();
   }
};

class Post
{
public:
   string id;
   list<Comment> comments;
   unordered_map<string, list<Comment>::iterator> postCommentsIdMap;

   string getUniqueId()
   {
      static int postId = 0;
      return "p" + to_string( postId++ );
   }

   Post()
   {
      id = getUniqueId();
   }
   void addComment(Comment &comm)
   {
      comments.push_front( comm );
      postCommentsIdMap[ comm.id ] = comments.begin();
   }

   void addNestedComment(string id, Comment &comm)
   {
      if(postCommentsIdMap.find(id) == postCommentsIdMap.end() )
      {
         cout << " Comment does not exists, Therefore no nested comment can be added here\n";
         return;
      }
      auto& it = postCommentsIdMap[ id ];
      it->addComment( comm );
   }

   void editComment( string parentId , string commentId, string msg)
   {
      if( postCommentsIdMap.find( parentId ) == postCommentsIdMap.end() )
      {
         cout << " Comment with parent Id does not exists, Therefore comment can be edited here\n";
         return;
      }
      auto& it = postCommentsIdMap[ parentId ];

      if(parentId == commentId )
      {
         it->msg = msg;
      }
      else
      {
         it->setNestedDescription( commentId, msg );
      }
   }
   void deleteComment(string parentId, string commentId)
   {
      if( postCommentsIdMap.find( parentId ) == postCommentsIdMap.end() )
      {
         cout << " Comment with parent Id does not exists, Therefore comment can be deleted here\n";
         return;
      }
      auto& it = postCommentsIdMap[ parentId ];

      if( parentId == commentId )
      {
         comments.erase( it );
         postCommentsIdMap.erase( parentId );
      }
      else
      {
         it->nestedDelete( commentId );
      }
   }
};

class User
{
public:
   string id;
   string name;
   string getUniqueId()
   {
      static int id = 0;
      return "u" + to_string( id++ );
   }

   User(string name)
   {
      this->id = getUniqueId( );
   }

   void addCommentToPost(Post & post, Comment &comment)
   {
      comment.userId = this->id;
      comment.postId = post.id;
      comment.parentId = comment.id;
      post.addComment( comment );
   }

   void replyToComment(Post &post, string parentId, Comment &comment)
   {
      comment.userId = this->id;
      comment.postId = post.id;
      comment.parentId = parentId;
      post.addNestedComment(parentId, comment );
   }

   bool editComment( Post& post, string parentId, string commentId, string msg )
   {
      if(post.postCommentsIdMap.find(parentId) == post.postCommentsIdMap.end() )
      {
         cout << " parent Comment Does not exist " << parentId << endl;
         return false;
      }
      auto &it = post.postCommentsIdMap[ parentId ];
      if(it->userId != this->id )
      {
         cout << " Unauthorized to edit the comment\n";
         return false;
      }
      post.editComment( parentId, commentId, msg );
      return true;
   }

   bool deleteComment( Post& post, string parentId, string commentId )
   {
      if( post.postCommentsIdMap.find( parentId ) == post.postCommentsIdMap.end() )
      {
         cout << " parent Comment Does not exist " << parentId << endl;
         return false;
      }
      auto& it = post.postCommentsIdMap[ parentId ];
      if( it->userId != this->id )
      {
         cout << " Unauthorized to edit the comment\n";
         return false;
      }
      post.deleteComment( parentId, commentId );
      return true;
   }
};

int main()
{
   cout << " Facebook Comment System\n";

   User u1( "L" );
   Comment c1( "First Comment" );
   Comment c2( "Second Comment" );
   Comment c22( "Second nested comment" );
   Comment c11( "First nested comment" );
   Comment c12( "First Second nested comment" );
   Comment c13( "First Third nested comment" );

   Post p;
   u1.addCommentToPost( p, c1 );
   u1.addCommentToPost( p, c2 );
   u1.replyToComment( p, c1.id, c11 );
   u1.replyToComment( p, c1.id, c12 );
   u1.replyToComment( p, c1.id, c13 );
   u1.replyToComment( p, c2.id, c22 );

   for( Comment c : p.comments )
   {
      cout << c.msg.c_str() << "\n";
      for( Comment cmt : c.comments )
         cout << "\t" << cmt.msg.c_str() << "\n";
   }

   cout << "***********************************************************************" << endl;

   string s12 = "1st 2nd comment";
   string s11 = "1st 1st comment";

   u1.editComment( p, c1.id, c11.id, s11 );

   for( Comment c : p.comments )
   {
      cout << c.msg.c_str() << "\n";
      for( Comment cmt : c.comments )
         cout << "\t" << cmt.msg.c_str() << "\n";
   }


   cout << "***********************************************************************" << endl;

   u1.deleteComment( p, c1.id, c12.id );
   for( Comment c : p.comments )
   {
      cout << c.msg.c_str() << "\n";
      for( Comment cmt : c.comments )
         cout << "\t" << cmt.msg.c_str() << "\n";
   }

   cout << "***********************************************************************" << endl;

   u1.deleteComment( p, c1.id, c1.id );
   for( Comment c : p.comments )
   {
      cout << c.msg.c_str() << "\n";
      for( Comment cmt : c.comments )
         cout << "\t" << cmt.msg.c_str() << "\n";
   }
   return 0;
   
}