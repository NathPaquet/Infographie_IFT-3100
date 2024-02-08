enum CursorType {
  NORMAL,
  NAVIGATION,
  SELECTION,
  DRAWING
};

class Cursor {
public:
  Cursor(CursorType type);

  void drawCursor(float x, float y);

  void SetCursorType(CursorType cursorType);

private:
  void drawNormalCursor(float x, float y);
  void drawNavigationCursor(float x, float y);
  void drawSelectionCursor(float x, float y);
  void drawDrawingCursor(float x, float y);
  CursorType type;
};