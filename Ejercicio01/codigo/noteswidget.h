#ifndef NOTESWIDGET_H
#define NOTESWIDGET_H

#include <QWidget>

class QTextEdit;
class QPushButton;

class NotesWidget : public QWidget
{
    Q_OBJECT

private:
    int taskId;
    QTextEdit *txtNotes;
    QPushButton *btnGuardar;

    void loadNotes();

private slots:
    void saveNotes();

public:
    explicit NotesWidget(int taskId, QWidget *parent = nullptr);
};

#endif // NOTESWIDGET_H