#define CREATE_EVENT(Class, ObjectType, Event)        \
	if((signal == Event) && ObjectType(EventObject))		\
		return new class::Class(EventSignal, EventName, After, EventContainer, EventObject);

CREATE_EVENT(sdpGtkEventAdjustmentChanged, GTK_IS_ADJUSTMENT, "changed");
CREATE_EVENT(sdpGtkEventAdjustmentValueChanged, GTK_IS_ADJUSTMENT, "value-changed");

CREATE_EVENT(sdpGtkEventToggleButtonToggled, GTK_IS_TOGGLE_BUTTON, "toggled");

CREATE_EVENT(sdpGtkEventButtonClicked, GTK_IS_BUTTON, "clicked");
CREATE_EVENT(sdpGtkEventButtonEnter, GTK_IS_BUTTON, "enter");
CREATE_EVENT(sdpGtkEventButtonLeave, GTK_IS_BUTTON, "leave");
CREATE_EVENT(sdpGtkEventButtonPressed, GTK_IS_BUTTON, "pressed");
CREATE_EVENT(sdpGtkEventButtonReleased, GTK_IS_BUTTON, "released");

CREATE_EVENT(sdpGtkEventCalendarDaySelected, GTK_IS_CALENDAR, "day-selected");
CREATE_EVENT(sdpGtkEventCalendarDaySelectedDoubleClick, GTK_IS_CALENDAR, "day-selected-gdouble-click");
CREATE_EVENT(sdpGtkEventCalendarMonthChanged, GTK_IS_CALENDAR, "month-changed");
CREATE_EVENT(sdpGtkEventCalendarNextMonth, GTK_IS_CALENDAR, "next-month");
CREATE_EVENT(sdpGtkEventCalendarNextYear, GTK_IS_CALENDAR, "next-year");
CREATE_EVENT(sdpGtkEventCalendarPrevMonth, GTK_IS_CALENDAR, "prev-month");
CREATE_EVENT(sdpGtkEventCalendarPrevYear, GTK_IS_CALENDAR, "prev-year");

CREATE_EVENT(sdpGtkEventCheckMenuItemToggled, GTK_IS_CHECK_MENU_ITEM, "toggled");

CREATE_EVENT(sdpGtkEventCTreeChangeFocusRowExpansion, GTK_IS_CTREE, "change-focus-row-expansion");
CREATE_EVENT(sdpGtkEventCTreeTreeCollapse, GTK_IS_CTREE, "tree-collapse");
CREATE_EVENT(sdpGtkEventCTreeTreeExpand, GTK_IS_CTREE, "tree-expand");
CREATE_EVENT(sdpGtkEventCTreeTreeMove, GTK_IS_CTREE, "tree-move");
CREATE_EVENT(sdpGtkEventCTreeTreeSelectRow, GTK_IS_CTREE, "tree-select-row");
CREATE_EVENT(sdpGtkEventCTreeTreeUnselectRow, GTK_IS_CTREE, "tree-unselect-row");

CREATE_EVENT(sdpGtkEventCListAbortColumnResize, GTK_IS_CLIST, "abort-column-resize");
CREATE_EVENT(sdpGtkEventCListClickColumn, GTK_IS_CLIST, "click-column");
CREATE_EVENT(sdpGtkEventCListEndSelection, GTK_IS_CLIST, "end-selection");
CREATE_EVENT(sdpGtkEventCListExtendSelection, GTK_IS_CLIST, "extend-selection");
CREATE_EVENT(sdpGtkEventCListResizeColumn, GTK_IS_CLIST, "resize-column");
CREATE_EVENT(sdpGtkEventCListRowMove, GTK_IS_CLIST, "row-move");
CREATE_EVENT(sdpGtkEventCListScrollHorizontal, GTK_IS_CLIST, "scroll-horizontal");
CREATE_EVENT(sdpGtkEventCListScrollVertical, GTK_IS_CLIST, "scroll-vertical");
CREATE_EVENT(sdpGtkEventCListSelectAll, GTK_IS_CLIST, "select-all");
CREATE_EVENT(sdpGtkEventCListSelectRow, GTK_IS_CLIST, "select-row");
CREATE_EVENT(sdpGtkEventCListStartSelection, GTK_IS_CLIST, "start-selection");
CREATE_EVENT(sdpGtkEventCListToggleAddMode, GTK_IS_CLIST, "toggle-add-mode");
CREATE_EVENT(sdpGtkEventCListToggleFocusRow, GTK_IS_CLIST, "toggle-focus-row");
CREATE_EVENT(sdpGtkEventCListUndoSelection, GTK_IS_CLIST, "undo-selection");
CREATE_EVENT(sdpGtkEventCListUnselectAll, GTK_IS_CLIST, "unselect-all");
CREATE_EVENT(sdpGtkEventCListUnselectRow, GTK_IS_CLIST, "unselect-row");

CREATE_EVENT(sdpGtkEventColorSelectionColorChanged, GTK_IS_COLOR_SELECTION, "color-changed");

CREATE_EVENT(sdpGtkEventContainerAdd, GTK_IS_CONTAINER, "add");
CREATE_EVENT(sdpGtkEventContainerCheckResize, GTK_IS_CONTAINER, "check-resize");
CREATE_EVENT(sdpGtkEventContainerFocus, GTK_IS_CONTAINER, "focus");
CREATE_EVENT(sdpGtkEventContainerRemove, GTK_IS_CONTAINER, "remove");
CREATE_EVENT(sdpGtkEventContainerSetFocusChild, GTK_IS_CONTAINER, "set-focus-child");

CREATE_EVENT(sdpGtkEventCurveCurveTypeChanged, GTK_IS_CURVE, "curve-type-changed");

CREATE_EVENT(sdpGtkEventDataDisconnect, GTK_IS_DATA, "disconnect");

CREATE_EVENT(sdpGtkEventEditableActivate, GTK_IS_EDITABLE, "activate");
CREATE_EVENT(sdpGtkEventEditableChanged, GTK_IS_EDITABLE, "changed");
CREATE_EVENT(sdpGtkEventEditableCopyClipboard, GTK_IS_EDITABLE, "copy-clipboard");
CREATE_EVENT(sdpGtkEventEditableCutClipboard, GTK_IS_EDITABLE, "cut-clipboard");
CREATE_EVENT(sdpGtkEventEditableDeleteText, GTK_IS_EDITABLE, "delete-text");
CREATE_EVENT(sdpGtkEventEditableInsertText, GTK_IS_EDITABLE, "insert-text");
CREATE_EVENT(sdpGtkEventEditableKillChar, GTK_IS_EDITABLE, "kill-gchar");
CREATE_EVENT(sdpGtkEventEditableKillLine, GTK_IS_EDITABLE, "kill-line");
CREATE_EVENT(sdpGtkEventEditableKillWord, GTK_IS_EDITABLE, "kill-word");
CREATE_EVENT(sdpGtkEventEditableMoveCursor, GTK_IS_EDITABLE, "move-cursor");
CREATE_EVENT(sdpGtkEventEditableMovePage, GTK_IS_EDITABLE, "move-page");
CREATE_EVENT(sdpGtkEventEditableMoveToColumn, GTK_IS_EDITABLE, "move-to-column");
CREATE_EVENT(sdpGtkEventEditableMoveToRow, GTK_IS_EDITABLE, "move-to-row");
CREATE_EVENT(sdpGtkEventEditableMoveWord, GTK_IS_EDITABLE, "move-word");
CREATE_EVENT(sdpGtkEventEditablePasteClipboard, GTK_IS_EDITABLE, "paste-clipboard");
CREATE_EVENT(sdpGtkEventEditableSetEditable, GTK_IS_EDITABLE, "set-editable");

CREATE_EVENT(sdpGtkEventHandleBoxChildAttached, GTK_IS_HANDLE_BOX, "child-attached");
CREATE_EVENT(sdpGtkEventHandleBoxChildDetached, GTK_IS_HANDLE_BOX, "child-detached");

CREATE_EVENT(sdpGtkEventInputDialogDisableDevice, GTK_IS_INPUT_DIALOG, "disable-device");
CREATE_EVENT(sdpGtkEventInputDialogEnableDevice, GTK_IS_INPUT_DIALOG, "enable-device");

CREATE_EVENT(sdpGtkEventMenuItemActivate, GTK_IS_MENU_ITEM, "activate");
CREATE_EVENT(sdpGtkEventMenuItemActivateItem, GTK_IS_MENU_ITEM, "activate-item");

CREATE_EVENT(sdpGtkEventListItemEndSelection, GTK_IS_LIST_ITEM, "end-selection");
CREATE_EVENT(sdpGtkEventListItemExtendSelection, GTK_IS_LIST_ITEM, "extend-selection");
CREATE_EVENT(sdpGtkEventListItemScrollHorizontal, GTK_IS_LIST_ITEM, "scroll-horizontal");
CREATE_EVENT(sdpGtkEventListItemScrollVertical, GTK_IS_LIST_ITEM, "scroll-vertical");
CREATE_EVENT(sdpGtkEventListItemSelectAll, GTK_IS_LIST_ITEM, "select-all");
CREATE_EVENT(sdpGtkEventListItemStartSelection, GTK_IS_LIST_ITEM, "start-selection");
CREATE_EVENT(sdpGtkEventListItemToggleAddMode, GTK_IS_LIST_ITEM, "toggle-add-mode");
CREATE_EVENT(sdpGtkEventListItemToggleFocusRow, GTK_IS_LIST_ITEM, "toggle-focus-row");
CREATE_EVENT(sdpGtkEventListItemUndoSelection, GTK_IS_LIST_ITEM, "undo-selection");
CREATE_EVENT(sdpGtkEventListItemUnselectAll, GTK_IS_LIST_ITEM, "unselect-all");

CREATE_EVENT(sdpGtkEventItemDeselect, GTK_IS_ITEM, "deselect");
CREATE_EVENT(sdpGtkEventItemSelect, GTK_IS_ITEM, "select");
CREATE_EVENT(sdpGtkEventItemToggle, GTK_IS_ITEM, "toggle");

CREATE_EVENT(sdpGtkEventListSelectChild, GTK_IS_LIST, "select-child");
CREATE_EVENT(sdpGtkEventListSelectionChanged, GTK_IS_LIST, "selection-changed");
CREATE_EVENT(sdpGtkEventListUnselectChild, GTK_IS_LIST, "unselect-child");

CREATE_EVENT(sdpGtkEventMenuShellActivateCurrent, GTK_IS_MENU_SHELL, "activate-current");
CREATE_EVENT(sdpGtkEventMenuShellCancel, GTK_IS_MENU_SHELL, "cancel");
CREATE_EVENT(sdpGtkEventMenuShellDeactivate, GTK_IS_MENU_SHELL, "deactivate");
CREATE_EVENT(sdpGtkEventMenuShellMoveCurrent, GTK_IS_MENU_SHELL, "move-current");
CREATE_EVENT(sdpGtkEventMenuShellSelectionDone, GTK_IS_MENU_SHELL, "selection-done");

CREATE_EVENT(sdpGtkEventNotebookSwitchPage, GTK_IS_NOTEBOOK, "switch-page");

CREATE_EVENT(sdpGtkEventStatusbarTextPopped, GTK_IS_STATUSBAR, "text-popped");
CREATE_EVENT(sdpGtkEventStatusbarTextPushed, GTK_IS_STATUSBAR, "text-pushed");

CREATE_EVENT(sdpGtkEventTipsQueryStartQuery, GTK_IS_TIPS_QUERY, "start-query");
CREATE_EVENT(sdpGtkEventTipsQueryStopQuery, GTK_IS_TIPS_QUERY, "stop-query");
CREATE_EVENT(sdpGtkEventTipsQueryWidgetEntered, GTK_IS_TIPS_QUERY, "widget-entered");
CREATE_EVENT(sdpGtkEventTipsQueryWidgetSelected, GTK_IS_TIPS_QUERY, "widget-selected");

CREATE_EVENT(sdpGtkEventToolbarOrientationChanged, GTK_IS_TOOLBAR, "orientation-changed");
CREATE_EVENT(sdpGtkEventToolbarStyleChanged, GTK_IS_TOOLBAR, "style-changed");

CREATE_EVENT(sdpGtkEventTreeItemCollapse, GTK_IS_TREE_ITEM, "collapse");
CREATE_EVENT(sdpGtkEventTreeItemExpand, GTK_IS_TREE_ITEM, "expand");
CREATE_EVENT(sdpGtkEventTreeSelectChild, GTK_IS_TREE, "select-child");
CREATE_EVENT(sdpGtkEventTreeSelectionChanged, GTK_IS_TREE, "selection-changed");
CREATE_EVENT(sdpGtkEventTreeUnselectChild, GTK_IS_TREE, "unselect-child");

CREATE_EVENT(sdpGtkEventWindowSetFocus, GTK_IS_WINDOW, "set-focus");

CREATE_EVENT(sdpGtkEventWidgetAddAccelerator, GTK_IS_WIDGET, "add-accelerator");
CREATE_EVENT(sdpGtkEventWidgetButtonPressEvent, GTK_IS_WIDGET, "button-press-event");
CREATE_EVENT(sdpGtkEventWidgetButtonReleaseEvent, GTK_IS_WIDGET, "button-release-event");
CREATE_EVENT(sdpGtkEventWidgetClientEvent, GTK_IS_WIDGET, "client-event");
CREATE_EVENT(sdpGtkEventWidgetConfigureEvent, GTK_IS_WIDGET, "configure-event");
CREATE_EVENT(sdpGtkEventWidgetDebugMsg, GTK_IS_WIDGET, "debug-msg");
CREATE_EVENT(sdpGtkEventWidgetDeleteEvent, GTK_IS_WIDGET, "delete-event");
CREATE_EVENT(sdpGtkEventWidgetDestroyEvent, GTK_IS_WIDGET, "destroy-event");
CREATE_EVENT(sdpGtkEventWidgetDragBegin, GTK_IS_WIDGET, "drag-begin");
CREATE_EVENT(sdpGtkEventWidgetDragDataDelete, GTK_IS_WIDGET, "drag-data-delete");
CREATE_EVENT(sdpGtkEventWidgetDragDataGet, GTK_IS_WIDGET, "drag-data-get");
CREATE_EVENT(sdpGtkEventWidgetDragDataReceived, GTK_IS_WIDGET, "drag-data-received");
CREATE_EVENT(sdpGtkEventWidgetDragDrop, GTK_IS_WIDGET, "drag-drop");
CREATE_EVENT(sdpGtkEventWidgetDragEnd, GTK_IS_WIDGET, "drag-end");
CREATE_EVENT(sdpGtkEventWidgetDragLeave, GTK_IS_WIDGET, "drag-leave");
CREATE_EVENT(sdpGtkEventWidgetDragMotion, GTK_IS_WIDGET, "drag-motion");
CREATE_EVENT(sdpGtkEventWidgetDraw, GTK_IS_WIDGET, "draw");
CREATE_EVENT(sdpGtkEventWidgetDrawDefault, GTK_IS_WIDGET, "draw-default");
CREATE_EVENT(sdpGtkEventWidgetDrawFocus, GTK_IS_WIDGET, "draw-focus");
CREATE_EVENT(sdpGtkEventWidgetEnterNotifyEvent, GTK_IS_WIDGET, "enter-notify-event");
CREATE_EVENT(sdpGtkEventWidgetEvent, GTK_IS_WIDGET, "event");
CREATE_EVENT(sdpGtkEventWidgetExposeEvent, GTK_IS_WIDGET, "expose-event");
CREATE_EVENT(sdpGtkEventWidgetFocusInEvent, GTK_IS_WIDGET, "focus-in-event");
CREATE_EVENT(sdpGtkEventWidgetFocusOutEvent, GTK_IS_WIDGET, "focus-out-event");
CREATE_EVENT(sdpGtkEventWidgetHide, GTK_IS_WIDGET, "hide");
CREATE_EVENT(sdpGtkEventWidgetKeyPressEvent, GTK_IS_WIDGET, "key-press-event");
CREATE_EVENT(sdpGtkEventWidgetKeyReleaseEvent, GTK_IS_WIDGET, "key-release-event");
CREATE_EVENT(sdpGtkEventWidgetLeaveNotifyEvent, GTK_IS_WIDGET, "leave-notify-event");
CREATE_EVENT(sdpGtkEventWidgetMap, GTK_IS_WIDGET, "map");
CREATE_EVENT(sdpGtkEventWidgetMapEvent, GTK_IS_WIDGET, "map-event");
CREATE_EVENT(sdpGtkEventWidgetMotionNotifyEvent, GTK_IS_WIDGET, "motion-notify-event");
CREATE_EVENT(sdpGtkEventWidgetNoExposeEvent, GTK_IS_WIDGET, "no-expose-event");
CREATE_EVENT(sdpGtkEventWidgetParentSet, GTK_IS_WIDGET, "parent-set");
CREATE_EVENT(sdpGtkEventWidgetPropertyNotifyEvent, GTK_IS_WIDGET, "property-notify-event");
CREATE_EVENT(sdpGtkEventWidgetProximityInEvent, GTK_IS_WIDGET, "proximity-in-event");
CREATE_EVENT(sdpGtkEventWidgetProximityOutEvent, GTK_IS_WIDGET, "proximity-out-event");
CREATE_EVENT(sdpGtkEventWidgetRealize, GTK_IS_WIDGET, "realize");
CREATE_EVENT(sdpGtkEventWidgetRemoveAccelerator, GTK_IS_WIDGET, "remove-accelerator");
CREATE_EVENT(sdpGtkEventWidgetSelectionClearEvent, GTK_IS_WIDGET, "selection-clear-event");
CREATE_EVENT(sdpGtkEventWidgetSelectionGet, GTK_IS_WIDGET, "selection-get");
CREATE_EVENT(sdpGtkEventWidgetSelectionNotifyEvent, GTK_IS_WIDGET, "selection-notify-event");
CREATE_EVENT(sdpGtkEventWidgetSelectionReceived, GTK_IS_WIDGET, "selection-received");
CREATE_EVENT(sdpGtkEventWidgetSelectionRequestEvent, GTK_IS_WIDGET, "selection-request-event");
CREATE_EVENT(sdpGtkEventWidgetShow, GTK_IS_WIDGET, "show");
CREATE_EVENT(sdpGtkEventWidgetSizeAllocate, GTK_IS_WIDGET, "size-allocate");
CREATE_EVENT(sdpGtkEventWidgetSizeRequest, GTK_IS_WIDGET, "size-request");
CREATE_EVENT(sdpGtkEventWidgetStateChanged, GTK_IS_WIDGET, "state-changed");
CREATE_EVENT(sdpGtkEventWidgetStyleSet, GTK_IS_WIDGET, "style-set");
CREATE_EVENT(sdpGtkEventWidgetUnmap, GTK_IS_WIDGET, "unmap");
CREATE_EVENT(sdpGtkEventWidgetUnmapEvent, GTK_IS_WIDGET, "unmap-event");
CREATE_EVENT(sdpGtkEventWidgetUnrealize, GTK_IS_WIDGET, "unrealize");
CREATE_EVENT(sdpGtkEventWidgetVisibilityNotifyEvent, GTK_IS_WIDGET, "visibility-notify-event");

CREATE_EVENT(sdpGtkEventObjectDestroy, GTK_IS_OBJECT, "destroy");
