#include "BookDialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialogButtonBox>

BookDialog::BookDialog(QString modalTitle, Book* book)
    : QDialog()
    , _book(book)
{
    this->setWindowTitle(modalTitle);
    QHBoxLayout* container = new QHBoxLayout();
    container->addSpacing(20);
    QVBoxLayout* body = new QVBoxLayout();
    container->addLayout(body);
    container->addSpacing(20);
    QLineEdit* titleInput = new QLineEdit(_book->getTitle());
    QLabel* titleLabel = new QLabel("Title");
    QLineEdit* authorInput = new QLineEdit(_book->getAuthor());
    QLabel* authorLabel = new QLabel("Author");
    QLineEdit* yearInput = new QLineEdit(QString::number(_book->getYear()));
    QLabel* yearLabel = new QLabel("Year");
    yearInput->setValidator(new QIntValidator());
    body->addWidget(titleLabel);
    body->addWidget(titleInput, 1);
    body->addSpacing(8);
    body->addWidget(authorLabel);
    body->addWidget(authorInput,1);
    body->addSpacing(8);
    body->addWidget(yearLabel);
    body->addWidget(yearInput,1);
    body->addSpacing(8);

    connect(titleInput,
        SIGNAL(textChanged(const QString&)),
        this,
        SLOT(setTitle(const QString&))
    );
    connect(authorInput,
        SIGNAL(textChanged(const QString&)),
        this,
        SLOT(setAuthor(const QString&))
    );
    connect(yearInput,
        SIGNAL(textChanged(const QString&)),
        this,
        SLOT(setYear(const QString&))
    );

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    body->addWidget(buttonBox);

    setLayout(container);
}

void BookDialog::setTitle(const QString& title)
{
    _book->setTitle(title);
}

void BookDialog::setAuthor(const QString& author)
{
    _book->setAuthor(author);
}

void BookDialog::setYear(const QString& year)
{
    _book->setYear(year.toInt());
}
