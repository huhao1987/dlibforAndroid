package au.hao.and.dlibmodule.Objects;

public class Rectangle {
    long left;
    long top;
    long right;
    long bottom;
    long area;
    long width;
    long height;
    public Rectangle(long left, long top, long right, long bottom){
        this.left=left;
        this.top=top;
        this.right=right;
        this.bottom=bottom;
    }
    public Rectangle(long width,long height)
    {
        this.width=width;
        this.height=height;
    }
    public long getLeft() {
        return left;
    }

    public void setLeft(long left) {
        this.left = left;
    }

    public long getTop() {
        return top;
    }

    public void setTop(long top) {
        this.top = top;
    }

    public long getRight() {
        return right;
    }

    public void setRight(long right) {
        this.right = right;
    }

    public long getBottom() {
        return bottom;
    }

    public void setBottom(long bottom) {
        this.bottom = bottom;
    }
    @Override
    public String toString() {
        return "Rectangle{" +
                "left=" + left +
                ", top=" + top +
                ", right=" + right +
                ", bottom=" + bottom +
                ",width="+width+
                ".height="+height+
                ",area="+area+
                '}';
    }
}
