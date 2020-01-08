package maze;

public class MPoint {
	private int left = 1;
	private int right = 1;
	private int up = 1;
	private int down = 1;
	private int x;
	private int y;
	private MPoint pre;//建立先置点，以配合广度遍历
	public boolean visted;

	public MPoint getPre() {
		return pre;
	}

	public void setPre(MPoint pre) {
		this.pre = pre;
	}

	public MPoint(int x, int y, MPoint pre, boolean visted) {
		super();
		this.x = x;
		this.y = y;
		this.pre = pre;
		this.visted = visted;
	}

	public MPoint(int x, int y) {
		this.x = x;
		this.y = y;
	}

	public int getLeft() {
		return left;
	}

	public void setLeft() {
		this.left = 0;
	}

	public int getRight() {
		return right;
	}

	public void setRight() {
		this.right = 0;
	}

	public int getUp() {
		return up;
	}

	public void setUp() {
		this.up = 0;
	}

	public int getDown() {
		return down;
	}

	public void setDown() {
		this.down = 0;
	}

	public int getX() {
		return x;
	}

	public void setX(int x) {
		this.x = x;
	}

	public int getY() {
		return y;
	}

	public void setY(int y) {
		this.y = y;
	}

}
