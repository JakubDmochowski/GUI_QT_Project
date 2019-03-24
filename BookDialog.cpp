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
    QLineEdit* titleInput = new QLineEdit();
    QLabel* titleLabel = new QLabel("Title");
    QLineEdit* authorInput = new QLineEdit();
    QLabel* authorLabel = new QLabel("Author");
    QLineEdit* yearInput = new QLineEdit();
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
        SLOT([=](const QString& value){
            this->_book->setTitle(value);
        })
    );

    QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    body->addWidget(buttonBox);

    setLayout(container);
}
