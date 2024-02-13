enum class CursorMode {
  NAVIGATION,
  SELECTION,
  DRAWING,
  ADDING,
  REMOVING
};

class Cursor {
public:
  Cursor(CursorMode type);

  void drawCursor(float x, float y);

  void setCursorMode(CursorMode cursorType);
  CursorMode getCursorMode() const;

private:
  void drawNavigationCursor(float x, float y);
  void drawSelectionCursor(float x, float y);
  void drawDrawingCursor(float x, float y);
  CursorMode mode;
};