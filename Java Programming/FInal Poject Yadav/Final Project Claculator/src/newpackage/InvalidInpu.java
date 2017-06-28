
package newpackage;


public class InvalidInpu extends Exception {
//======================================================================
// [FUNC] Primary class constructor with no parameters.
public InvalidInpu() {
	super();
}

//======================================================================
// [FUNC] Constructor accepting exception message as parameter.
public InvalidInpu(String msg) {
	super(msg);
}
}
