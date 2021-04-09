import myservice.MySPI;

/*open*/ module Library {
  exports myservice;
  opens myservice to Client;
  provides MySPI with serviceimp.MyImpl;
}